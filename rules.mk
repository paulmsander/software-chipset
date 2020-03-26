# rules.mk -- This file contains rules that are used by all of the components
#             comprising the Software ChipSet component library.

# This file is part of a suite of programs called Software Chipset.
# The source code for Software Chipset has been released into the
# public domain by its author, Paul Sander.

# Default rule, just in case

all:

# Install the libraries in $(LIBDIR), which is passed on the command line
# or set in common.mk

installLib:
	for x in $?;							\
	do								\
		cp $$x $(LIBDIR);					\
		$(RANLIB) $(LIBDIR)/$$x					\
		chmod 644 $(LIBDIR)/$$x;				\
	done

# Install the include files in $(INCDIR), which is passed on the command line
# or set in common.mk

installInclude:
	for x in $?;							\
	do								\
		cp $$x $(INCDIR);					\
		chmod 644 $(INCDIR)/$$x;				\
	done

# Install the documentation

installDocs:
	for x in $?;							\
	do								\
		dest=`expr $$x : '\(.*\)\.[^.]*'`.$(MANSUFF)$(INSTALLSUFF); \
		< $$x $(INSTALLMAN) > $(MANDIR)/$$dest;			\
		chmod 644 $(MANDIR)/$$dest;				\
	done

# Make all products locally

everything: all docs

# Install everything

install: installInclude installLib installDocs

# Clean-up

clean:
	if [ -d gct_backup ];			\
	then					\
		grestore;			\
		rmdir gct_backup || true;	\
	fi
	if [ -d gct_backup ];		\
	then				\
		mv gct_backup/* .;	\
		rmdir gct_backup;	\
	fi
	rm -f *.o test core gct*.c gct*.h __gct-* gct-map gct-rscript gct-log

spotless clobber realclean veryclean: clean
	rm -f *.doc *.ps *.$(MANSUFF) *.$(LIBSUFF) conf.h

# Create the MANIFEST file

MANIFEST: clobber
	find . -type f -print | sed -e 's/^\.\///' -e /CVS/d | sort > MANIFEST

# Instrument code for GCT coverage analysis

gct:
	gct-init;
	$(MAKE) objects "CC=gct $(INCLUDES)"
	$(CC) -c gct-ps-defs.c
	$(CC) -c gct-write.c
	$(MAKE) test.o "CFLAGS=$(CFLAGS) -DGCT"
	$(MAKE) all "GCTSTUFF=gct-ps-defs.o gct-write.o"
	grestore

### End of File ###
