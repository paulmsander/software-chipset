# rules.mk -- This file contains rules that are used by all of the components
#             comprising the Software ChipSet component library.

# This file is part of a suite of programs called Software Chipset.
# The source code for Software Chipset has been released into the
# public domain by its author, Paul Sander.

# Identify the tree roots.  These settings assume that the developer is
# working in a single rooted workspace.  The top-level Makefile overrides
# these when building the entire library, possibly in a multi-rooted
# workspace.

THISDIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
BUILDROOT ?= $(THISDIR)
SRCROOT ?= $(THISDIR)

include $(SRCROOT)/common.mk

# Main chipset library

LIBCHIPSET = $(LIBDIR)/libchipset.a

# Default rule

.PHONY: all
all: $(LIBCHIPSET)

# Pattern rule to copy a header file from the source tree to the
# include directory of the build tree.

$(INCDIR)/%.h: %.h
	mkdir -p $(@D)
	cp $< $@
	chmod a+r $@

# Pattern rule to compile a C source file and store the object file in
# the obj directory of the build tree.

CFLAGS = -I$(INCDIR)

define MAKEDEP
	$(CC) $(CFLAGS) -M -o - $< | \
	sed -e '1s/:/:\\'$$'\\\n /' | \
	( echo "# This Makefile applies in $(CURDIR)"; \
	  echo '# $$(info Reading $(TESTDIR)/$(@F).d)'; \
	  echo "$@: \\" ; \
	  sed -e '1d' )
endef

$(OBJDIR)/%.o: %.c
	mkdir -p $(@D) $(TESTDIR)
	$(MAKEDEP) > $(TESTDIR)/$(@F).d
	$(CC) $(CFLAGS) -c -o $@ $<

$(TESTDIR)/%.o: %.c
	mkdir -p $(@D)
	$(MAKEDEP) > $@.d
	$(CC) $(CFLAGS) -c -o $@ $<

# Override built-in pattern rule to compile test programs when
# SRCROOT and BUILDROOT are the same directory.

%.o: %.c
	mkdir -p $(@D)
	$(MAKEDEP) > $@.d
	$(CC) $(CFLAGS) -c -o $@ $<

sinclude $(wildcard $(TESTDIR)/*.d)

# Pattern rule to create an archive library from a list of object files.

$(LIBDIR)/%.a:
	mkdir -p $(@D)
	$(AR) r $@ $^
	chmod a+r $@

# Pattern rule to link an executable.

LD = $(CC)
LFLAGS = -L$(LIBDIR)

$(BINDIR)/%: $(OBJDIR)/%.o
	mkdir -p $(@D)
	$(LD) $(LFLAGS) -o $@ $^

# Pattern rule to link unit tests.

$(TESTDIR)/%: $(TESTDIR)/%.o
	mkdir -p $(@D)
	$(LD) $(LFLAGS) -o $@ $^

# Pattern rule to copy man pages.

$(MANDIR)/%.$(MANSECT): %.man
	mkdir -p $(@D)
	cp $< $@
	chmod a+r $@

# Rule to clean the build area.

.PHONY: clean
clean::
	rm -rf $(BINDIR) $(INCDIR) $(LIBDIR) $(OBJDIR) $(SHAREDIR)

ifneq ($(realpath $(BUILDROOT)),$(realpath $(SRCROOT)))
clean::
	: rm -rf $(BUILDROOT)/src
endif

.PHONY: spotless clobber realclean veryclean
spotless clobber realclean veryclean: clean

## Install the libraries in $(LIBDIR), which is passed on the command line
## or set in common.mk
#
#installLib:
#	for x in $?;							\
#	do								\
#		cp $$x $(LIBDIR);					\
#		$(RANLIB) $(LIBDIR)/$$x					\
#		chmod 644 $(LIBDIR)/$$x;				\
#	done
#
## Install the include files in $(INCDIR), which is passed on the command line
## or set in common.mk
#
#installInclude:
#	for x in $?;							\
#	do								\
#		cp $$x $(INCDIR);					\
#		chmod 644 $(INCDIR)/$$x;				\
#	done
#
## Install the documentation
#
#installDocs:
#	for x in $?;							\
#	do								\
#		dest=`expr $$x : '\(.*\)\.[^.]*'`.$(MANSUFF)$(INSTALLSUFF); \
#		< $$x $(INSTALLMAN) > $(MANDIR)/$$dest;			\
#		chmod 644 $(MANDIR)/$$dest;				\
#	done
#
## Make all products locally
#
#everything: all docs
#
## Install everything
#
#install: installInclude installLib installDocs
#
## Clean-up
#
#clean:
#	if [ -d gct_backup ];			\
#	then					\
#		grestore;			\
#		rmdir gct_backup || true;	\
#	fi
#	if [ -d gct_backup ];		\
#	then				\
#		mv gct_backup/* .;	\
#		rmdir gct_backup;	\
#	fi
#	rm -f *.o test core gct*.c gct*.h __gct-* gct-map gct-rscript gct-log
#
#spotless clobber realclean veryclean: clean
#	rm -f *.doc *.ps *.$(MANSUFF) *.$(LIBSUFF) conf.h
#
## Create the MANIFEST file
#
#MANIFEST: clobber
#	@set -x; \
#	find . -type f -print | \
#	sed -e 's/^\.\///' | \
#	sed -e /CVS/d | \
#	fgrep -v .git | \
#	LANG=C sort > $@
#
## Instrument code for GCT coverage analysis
#
#gct:
#	gct-init;
#	$(MAKE) objects "CC=gct $(INCLUDES)"
#	$(CC) -c gct-ps-defs.c
#	$(CC) -c gct-write.c
#	$(MAKE) test.o "CFLAGS=$(CFLAGS) -DGCT"
#	$(MAKE) all "GCTSTUFF=gct-ps-defs.o gct-write.o"
#	grestore
#
#### End of File ###
