# This is the Makefile for the Software ChipSet.  Edit this as needed
# for your system.  This makefile works properly with brain-dead SVR2
# make, so it should work with your tool, too.
#
# The "all" target installs all of the components in a single library
# rooted in this directory.  The "install" target installs that library
# and the include files and documents in an appropriate place.
#
# This file is part of a suite of programs called Software Chipset.
# The source code for Software Chipset has been released into the
# public domain by its author, Paul Sander.

include common.mk

# This rule verifies that all of the Software ChipSet's files have unpacked
# correctly.

verify:
	ok=1;								\
	if [ ! -f MANIFEST ];						\
	then								\
		echo MANIFEST file missing from top-level directory;	\
		ok=0;							\
	elif [ ! -d src ];						\
	then								\
		echo There is no source code for the components;	\
		echo Source code belongs in directories contained in;	\
		echo the directory '"./src"';				\
		ok=0;							\
	else								\
		for x in $(COMPONENTS);					\
		do							\
			if [ "$$x" = "CVS" ];				\
			then						\
				continue;				\
			fi;						\
			echo Checking ./src/$$x;			\
			if [ -d ./src/$$x ];				\
			then						\
				cd ./src/$$x;				\
				if [ ! -f MANIFEST ];			\
				then					\
					echo MANIFEST missing from ./src/$$x;\
					ok=0;				\
				else					\
					thisOk=1;			\
					for y in `cat MANIFEST`;	\
					do				\
						if [ ! -f $$y ];	\
						then			\
							echo $$y missing from ./src/$$x;\
							thisOk=0;	\
						fi;			\
					done;				\
					if [ $$thisOk = 0 ];		\
					then				\
						ok=0;			\
					fi;				\
				fi;					\
				cd ../..;				\
			fi;						\
		done;							\
	fi;								\
	if [ "$$ok" = 0 ];						\
	then								\
		echo Failed to verify installation;			\
		false;							\
	else								\
		echo Installation is okay;				\
	fi;								\

# This rule builds the staging area rooted in the present working directory.

prep:
	echo '*** Prepping ***'
	if [ ! -d $(STAGE) ];						\
	then								\
		echo The $(STAGE) directory does not exist.  Please;	\
		echo create it.;					\
		false;						\
	else								\
		for x in $(STAGEINC) $(STAGELIB) $(STAGEMAN)	 	\
		         $(STAGEMAN)/man3 $(STAGETMP);			\
		do							\
			if [ ! -d "$$x" ];				\
			then						\
				mkdir $$x;				\
			fi;						\
		done;							\
	fi

# This rule makes the "installInclude," "installLib," and "installDocs"
# targets in each of the source directories, forcing their ROOT macros
# to point to here.  Thus, installed under this directory are the
# include files first (since some components may depend on others),
# then the libraries and documentation.  Finally, the libchipset.a
# library is built.

all: prep
	root=$(STAGE);							\
	incdir=$(STAGEINC);						\
	libdir=$(STAGELIB);						\
	mandir=$(STAGEMAN)/man3;					\
	for t in installInclude installDocs;				\
	do								\
		for x in $(COMPONENTS);					\
		do							\
			if [ -f "src/$$x/Makefile" ];			\
			then						\
				echo '***' Building $$x $$t '***';	\
				( cd src/$$x && make $$t ROOT=$$root	\
					INCDIR=$$incdir			\
					LIBDIR=$$libdir			\
					MANDIR=$$mandir			\
				);					\
				echo;					\
			else						\
				echo '***' No Makefile in $$x '***';	\
			fi;						\
		done;							\
	done;								\
	echo '***' Building libchipset.$(LIBSUFF) library '***';	\
	for x in $(COMPONENTS);						\
	do								\
		if [ -f "src/$$x/Makefile" ];				\
		then							\
			echo '***' Building $$x installLib '***';	\
			( cd src/$$x &&					\
			  make ROOT=$$root				\
			       INCDIR=$$incdir				\
			       LIBDIR=$$libdir				\
			       MANDIR=$$mandir				\
			       installLib				\
			);						\
			( cd src/$$x &&					\
			  make TARGET=$$root/lib/libchipset.$(LIBSUFF)	\
			       ROOT=$$root				\
			       INCDIR=$$incdir				\
			       LIBDIR=$$libdir				\
			       MANDIR=$$mandir				\
			       $$root/lib/libchipset.$(LIBSUFF)		\
			);						\
			echo;						\
		else							\
			echo '***' No Makefile in $$x '***';		\
		fi;							\
	done;

# This rule installs the manpages.  It scans the man directory, and
# makes sure a corresponding one exists in the install tree.  Then
# it copies all of the manpages it finds into the install tree, one
# directory at a time.

installDocs:
	if [ ! -d $(DESTMAN) ];						\
	then								\
		echo $(DESTMAN) does not exist.  Please create it.;	\
		false;							\
	fi
	echo '***' Installing manpages '***'
	cd $(STAGEMAN);							\
	for sec in *;							\
	do								\
		if [ -d $$sec -a -d $(DESTMAN)/$$sec ];			\
		then							\
		(							\
			cd $$sec;					\
			for f in *;					\
			do						\
				if [ -f $$f ];				\
				then					\
					cp $$f $(DESTMAN)/$$sec/$$f;	\
					chmod 644 $(DESTMAN)/$$sec/$$f;	\
				fi;					\
			done;						\
		);							\
		else							\
			echo $(DESTMAN)/$$sec does not exist.;		\
			echo Please create it.;				\
			false;						\
			break;						\
		fi;							\
	done;

# This rule copies all of the include files into the install tree.

installInclude:
	if [ ! -d $(DESTINC) ];						\
	then								\
		echo $(DESTINC) does not exist.  Please create it.;	\
		false;							\
	fi
	echo '***' Installing include files '***'
	cd $(STAGEINC);							\
	for x in *;							\
	do								\
		if [ -f $$x ];						\
		then							\
			cp $$x $(DESTINC);				\
			chmod 644 $(DESTINC)/$$x;			\
		fi;							\
	done

# This rule copies the libchipset.a file to the install tree, and
# ranlibs it if necessary.

installLib:
	if [ ! -d $(DESTLIB) ];						\
	then								\
		echo $(DESTLIB) does not exist.  Please create it.;	\
		false;							\
	fi
	echo '***' Installing library '***'
	cp $(STAGELIB)/libchipset.$(LIBSUFF) $(DESTLIB)
	$(RANLIB) $(DESTLIB)/libchipset.$(LIBSUFF)
	chmod 644 $(DESTLIB)/libchipset.$(LIBSUFF)

# This rule installs public header files, libchipset.a, and the manpages.

install: all installDocs installInclude installLib
	echo '***' Installation complete '***'

# This rule builds and runs the self-tests for each component.

test: all
	if [ ! -d $(STAGETMP) ];					\
	then								\
		mkdir $(STAGETMP);					\
	fi;								\
	rm -f $(STAGETMP)/test.out;					\
	touch $(STAGETMP)/test.out;					\
	for x in $(COMPONENTS);						\
	do								\
	(								\
		if [ ! -f src/$$x/Makefile ];				\
		then							\
			continue;					\
		fi;							\
		echo "Testing $$x:";					\
		echo "Testing $$x:" >> $(STAGETMP)/test.out;		\
		cd src/$$x;						\
		make test ROOT=$(STAGE) INCDIR=$(STAGEINC)		\
			LIBDIR=$(STAGELIB) MANDIR=$(STAGEMAN);		\
		if [ "$$?" -ne 0 ];					\
		then							\
			echo "FAILED to build test" >> $(STAGETMP)/test.out;\
			echo "FAILED to build test";			\
			false;						\
			break;						\
		else							\
			./test >> $(STAGETMP)/test.out;			\
			if [ "$$?" -ne 0 ];				\
			then						\
				echo "FAILED test";			\
				false;					\
				break;					\
			else						\
				echo "PASSED test";			\
			fi;						\
		fi;							\
	);								\
	done;								\
	if [ "$$?" -ne 0 ];						\
	then								\
		echo "---- FAILED ----";				\
	else								\
		echo "---- PASSED ----";				\
	fi

# This rule cleans intermediate files by cleaning the staging area
# and doing a "make clean" in all of the component source directories.

clean:
	if [ -d $(STAGELIB) ];						\
	then								\
		cd $(STAGELIB);						\
		> /dev/null 2>&1 files=* true;				\
		if [ "$$files" != "" ];					\
		then							\
			for x in $$files;				\
			do						\
				if [ "$$x" != "libchipset.$(LIBSUFF)" ];\
				then					\
					rm $$x;				\
				fi;					\
			done;						\
		fi;							\
	fi
	for x in $(COMPONENTS);						\
	do								\
		if [ -d src/$$x -a -f src/$$x/Makefile ];		\
		then							\
			echo '***' Cleaning $$x '***';			\
			( cd src/$$x && make clean );			\
		fi;							\
	done
	rm -rf $(STAGETMP)

# This rule attempts to return to pristine sources by removing all
# installed files from the staging area, and doing a "make spotless"
# in each of the component source directories.

spotless clobber realclean veryclean:
	rm -rf $(STAGEINC) $(STAGELIB) $(STAGETMP) $(STAGEMAN) $(STAGEINST)
	rm -f temp
	for x in $(COMPONENTS);						\
	do								\
		if [ -d src/$$x -a -f src/$$x/Makefile ];		\
		then							\
			echo '***' Scrubbing $$x '***';			\
			( cd src/$$x && make spotless );		\
		fi;							\
	done

MANIFEST: clobber
	find . -type f -print |						\
		sed -e 's/^\.\///' -e /CVS/d -e /header/d -e '/\.git/d' |\
		LANG=C sort > MANIFEST
	for x in $(COMPONENTS);						\
	do								\
		echo Processing $$x;					\
		( cd src/$$x && make MANIFEST );			\
	done

# This rule builds a shar file using Rich $alz's shar implementation.

shar:
	for x in $(STAGETMP) $(STAGEINST);				\
	do								\
		if [ ! -d $$x ];					\
		then							\
			mkdir $$x;					\
		fi;							\
	done
	cp MANIFEST $(STAGETMP)/MANIFEST
	echo src >> $(STAGETMP)/MANIFEST
	for x in $(COMPONENTS);						\
	do								\
		if [ -f src/$$x/Makefile -a -f src/$$x/MANIFEST ];	\
		then							\
			echo src/$$x >> $(STAGETMP)/MANIFEST;		\
		fi;							\
	done
	for x in $(COMPONENTS);						\
	do								\
		if [ -f src/$$x/Makefile -a -f src/$$x/MANIFEST ];	\
		then							\
			echo "Processing $$x";				\
			sed -e "s/^/src\/$$x\//g" src/$$x/MANIFEST	\
				>> $(STAGETMP)/MANIFEST;		\
		fi;							\
	done
	makekit -n$(STAGEINST)/ChipSet.part -s30k 			\
		"-tNow edit common.mk and do a 'make all'"		\
		< $(STAGETMP)/MANIFEST
	rm $(STAGETMP)/MANIFEST

# This rule builds a portable cpio archive.

cpio:
	for x in $(STAGETMP) $(STAGEINST);				\
	do								\
		if [ ! -d $$x ];					\
		then							\
			mkdir $$x;					\
		fi;							\
	done
	cp MANIFEST $(STAGETMP)/MANIFEST
	for x in $(COMPONENTS);						\
	do								\
		if [ -f src/$$x/Makefile -a -f src/$$x/MANIFEST ];	\
		then							\
			echo "Processing $$x";				\
			sed -e "s/^/src\/$$x\//g" src/$$x/MANIFEST	\
				>> $(STAGETMP)/MANIFEST;		\
		fi;							\
	done
	cpio -ocv < $(STAGETMP)/MANIFEST | gzip -c 			\
		> $(STAGEINST)/ChipSet.cpio.gz
	rm $(STAGETMP)/MANIFEST

# This rule builds a tar archive.

tar:
	for x in $(STAGETMP) $(STAGETMP)/ChipSet			\
		 $(STAGETMP)/ChipSet/src $(STAGEINST);			\
	do								\
		if [ ! -d $$x ];					\
		then							\
			mkdir $$x;					\
		fi;							\
	done
	cp MANIFEST $(STAGETMP)/MANIFEST
	for x in $(COMPONENTS);						\
	do								\
		if [ -f src/$$x/Makefile -a -f src/$$x/MANIFEST ];	\
		then							\
			echo "Processing $$x";				\
			sed -e "s/^/src\/$$x\//g" src/$$x/MANIFEST	\
				>> $(STAGETMP)/MANIFEST;		\
			mkdir $(STAGETMP)/ChipSet/src/$$x;		\
		fi;							\
	done
	(								\
		read x;							\
		while [ "$$x" != "" ];					\
		do							\
			y="$(STAGETMP)/ChipSet/`dirname $$x`";		\
			if [ ! -d "$$y" ];				\
			then						\
				echo Creating directory $$y;		\
				mkdir "$$y";				\
			fi;						\
			echo Linking $$x;				\
			ln $$x $(STAGETMP)/ChipSet/$$x;			\
			read x;						\
		done;							\
		true;							\
	) < $(STAGETMP)/MANIFEST
	( cd $(STAGETMP)/ChipSet; tar cf - . ) | gzip -c 		\
		> $(STAGEINST)/ChipSet.tar.gz
	rm -rf $(STAGETMP)/MANIFEST $(STAGETMP)/ChipSet

# This rule builds a zip archive.

zip:
	for x in $(STAGETMP) $(STAGETMP)/ChipSet 			\
		 $(STAGETMP)/ChipSet/src $(STAGEINST);			\
	do								\
		if [ ! -d $$x ];					\
		then							\
			mkdir $$x;					\
		fi;							\
	done
	cp MANIFEST $(STAGETMP)/MANIFEST
	for x in $(COMPONENTS);						\
	do								\
		if [ -f src/$$x/Makefile -a -f src/$$x/MANIFEST ];	\
		then							\
			echo "Processing $$x";				\
			sed -e "s/^/src\/$$x\//g" src/$$x/MANIFEST	\
				>> $(STAGETMP)/MANIFEST;		\
			mkdir $(STAGETMP)/ChipSet/src/$$x;		\
		fi;							\
	done
	(								\
		read x;							\
		while [ "$$x" != "" ];					\
		do							\
			echo Linking $$x;				\
			ln $$x $(STAGETMP)/ChipSet/$$x;			\
			read x;						\
		done;							\
		true;							\
	) < $(STAGETMP)/MANIFEST
	rm -f $(STAGEINST)/ChipSet.zip
	echo Software ChipSet |						\
		( cd $(STAGETMP)/ChipSet;				\
		  NOZIP=":" zip -rnsz $(STAGEINST)/ChipSet.zip . )
	rm -rf $(STAGETMP)/MANIFEST $(STAGETMP)/ChipSet

# This rule builds arc archives for each component plus the scaffolding.
# This remains undocumented because the archive files are cumbersome to
# unpack, and because the unpacked source files are not suitable for
# compilation on Unix systems.

arc:
	if [ ! -d $(STAGEINST) ]; then mkdir $(STAGEINST); fi
	rm -f $(STAGEINST)/*.arc
	arc ais $(STAGEINST)/ChipSet.arc `cat MANIFEST`
	for x in $(COMPONENTS);						\
	do								\
		if [ -f src/$$x/Makefile -a -f src/$$x/MANIFEST ];	\
		then							\
		(							\
			cd src/$$x;					\
			arc ais $(STAGEINST)/$$x.arc `cat MANIFEST`;	\
		);							\
		fi;							\
	done

### End of file ###

