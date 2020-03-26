This file describes the build scaffolding provided with the Software ChipSet,
how it is implemented, and how it can be extended to support new components
that may be added in the future.  For instructions on building and installing
the Software ChipSet, please see the file named "INSTALL" in this directory.

The build scaffolding consists of four parts:  The top-level makefile, the
common.mk file, the rules.mk file, and the individual makefiles provided
with the source code for each component.  The common.mk file contains
configurable macros and rules that must be tailored for each installation,
and that are used by all of the makefiles during the build and installation.
The rules.mk file contains rules that are used by each of the component
makefiles during the build.  Each component makefile contains instructions for
building its particular component, testing its component, and installing its
products into a staging area.  The top-level makefile coordinates the actions
of the individual component makefiles, contains instructions for installing
the contents of the staging area and onto a live system, and more instructions
to for building archives that can be used to distribute copies of the
components.

These four parts work together to provide a flexible environment in which
a developer can build and test new components in several contexts.  The
developer is able to invoke "make" in each component source directory for
testing purposes.  Once a component works in isolation, it can then be tested
with the entire Software ChipSet by installing it into a staging area, which
is done by invoking "make" in the Software ChipSet top-level directory.
Components can be built and tested singly or in combination with one or more
others.

The Software ChipSet distribution has the following directory structure:

	chipset
	  src
	    btree
	    list
            ...

The "chipset" directory is the top-level directory, which contains this
file.  The "src" directory contains the source directories for each component.
Two examples are listed above, "btree" and "list".  The top-level makefile,
common.mk, and rules.mk are all contained in the "chipset" directory, while
each component also has its own makefile.

In addition to the source tree described above, the build scaffolding
maintains a staging area into which the components are installed for testing.
When the Software ChipSet is installed onto a live system, the installed
files are copied from this staging area.  The staging area has the following
structure by default (but this can be modified by configuring the common.mk
file):

	staging
	  include
	  install
	  lib
	  man
	    man3
	  tmp

The "staging" directory is the root directory of the staging area, and is
/tmp/ChipSet by default.  (It can be any directory except the src directory
above).  The "include" directory contains public header files provided by
each component, that are #include'd by client applications.  The "install"
directory contains new distributions of the Software ChipSet, if any are
desired.  The "lib" directory contains individual component libraries and the
libchipset.a library (which contains the sum of all of the code and data
contained by the other .a files contained in that directory).  The "man/man3"
directory contains man pages formatted according to the requirements of the
host system's "man" command.  (Typical formats are troff source files, ASCII
plaintext, and compressed plaintext.)  The "tmp" directory is used as a
scratch area when building libraries and distribution media.

A top-level build that installs into the staging area peforms these steps:
1.  Verify the structure of the staging area.  Either issue error messages or
    take corrective action if something is missing.
2.  Install public header files for each component into the staging area's
    "include" directory.  This is because some components may rely on the
    public headers of other components, and there may be loops in the
    dependencies.  Public header files may be source code, or they may be
    derived.  If they are derived, then they are built at this time.  Note
    that no component's public header files can require the presence of
    another's public header files at this stage of the build.
3.  Each component's documentation is built and installed into the staging
    area's "man/man3" directory.
4.  Each component's library is built and installed into the staging area's
    "lib" directory.  The "ranlib" program is invoked (if needed) on every
    .a file that is installed.
5.  The object files are extracted from every component's .a file contained
    in the staging area's "lib" directory, and installed in the libchipset.a
    file, also contained in the staging area's "lib" directory.  The "tmp"
    directory is used as a scratchpad to hold copies of the library modules
    temporarily.

A component's makefile may contain other targets that are incidental to the
building of the above targets.

Each of the components' makefiles include the common.mk file, which defines
the following macros:

SHELL -- The fullpath to the shell that used to by the recipies to
         perform each step of the build.  This should be /bin/sh or
         something that is 100% upward compatible.
COMPONENTS -- A list of the components that are affected by the
              build in progress.  This defaults to "`/bin/ls ./src`"
              and therefore contains all of the components, but can
              overridden on the command line.
STAGE -- The root of the staging area.  This must be configured by
         the user.  This is where components are installed by performing
         a "make" in the top level directory.  
STAGEINC -- The "include" directory of the staging area, defaulting
            to "$(STAGE)/include".
STAGELIB -- The "lib" directory of the staging area, defaulting to
            "$(STAGE)/lib".
STAGEMAN -- The "man" directory of the staging area, defaulting to
            "$(STAGE)/man".  The "man3" directory is always created
            inside this directory.
STAGETMP -- The "tmp" directory of the staging area, defaulting to
            "$(STAGE)/tmp".
STAGEINST -- The "install" directory of the staging area, defaulting
             to "$(STAGE)/install".
DEST -- The root of directory tree of the live system into which the
        Software ChipSet is ultimately installed.  This defaults to
        "/usr/local" but should be configured by the user.
DESTINC -- The "include" directory of the live system into which the
           Software ChipSet is ultimately installed.  This defaults
           to "$(DEST)/include".
DESTLIB -- The "lib" directory of the live system into which the
           Software ChipSet is ultimately installed.  This defaults
           to "$(DEST)/lib".
DESTMAN -- The "man" directory of the live system into which the
           Software ChipSet is ultimately installed.  This defaults
           to "$(DEST)/man".  The "man3" directory is assumed to
           exist prior to installation.
ROOT -- The root of the directory tree in which the developer of new
        components works.  This is directory tree is typically the
        same as the staging area, so the value of this macro defaults
        to "$(STAGE)".  This is where components are installed when a
        developer does a "make install" in any component source directory.
INCDIR -- The "include" directory of the developer's work area.  This
          defaults to "$(STAGEINC)".
LIBDIR -- The "lib" directory of the developer's work area.  This
          defaults to "$(STAGELIB)".
MANDIR -- The "man" directory of the developer's work area.  This
          defaults to "$(STAGEMAN)".  The man3 directory is created
          necessary.
INCLUDES -- This macro contains a C compiler's "-I" options as
            appropriate to locate the public header files needed when
            a component is built.  This defaults to "-I$(INCDIR)".
LIBSEARCH -- This macro contains a linker's "-L" options as
             appropriate to locate the component library files needed
             when building or running a component's test case.  It
             defaults to "-L$(LIBDIR)".
CC -- The name of the native C compiler.
CFLAGS -- Options to be given on the C compiler's command line.
LD -- The name of the native linkage editor.
LDFLAGS -- Options to be given on the linker's command line.
TESTLIBS -- This macro contains "-l" options or fullpaths to other
            libraries or object files that must be available to
            produce a component's test case.  This defaults to the null
            string.
MANSUFF -- The extension to a man page's file name after installation
           onto a live system.  This defaults to "3l".
RANLIB -- The fullpath to the "ranlib" program.  This is used on all
          systems, and should be set to /bin/true if ranlib is not available.
AR -- The command used to build a library from object files.  For statically
      linked libraries, this is normally set to "ar r".  For shared libraries,
      it is set to some platform-specific value.  The first argument must
      be the name of the library, and the remaining arguments are the names
      of object files, which can be paths.
LIBSUFF -- The extention that appears at the end of the name of a library.
           For statically linked libraries, this is normally "a".  For shared
           libraries, it is set to a platform-specific value.
PSROFF -- A filter that translates Troff source to PostScript.  This defaults
          to "psroff -t -man".  Another common value is
          "troff -Tpsc -man | psdit".
NROFF -- A filter that translates Troff source to ASCII plaintext.  This
         defaults to "nroff -man | col -b -x", though another common value is
         simply "nroff -man".
COMPRESS -- A filter that compresses ASCII plaintext.  This is used to compress
            man pages on those systems that support it.  This defaults to
            "compress", but should be "/bin/cat" on systems that do not support
            compressed man pages.
ZSUFF -- The extension appended to a man page's file name and
         $(MANSUFF) extension if the target system requires its
         man pages to be compressed.  The default value is ".Z", but should
         be the null string on systems that do not support compressed man
         pages.
INSTALLMAN -- A filter that reads a man page in Troff source form
              and produces a file in the proper format for the target
              system's "man" command.  This defaults to
              "$(NROFF) | $(COMPRESS)".  On systems that support man pages
              in Troff source form, this should be "/bin/cat".
INSTALLSUFF -- The extension added to the file name of a correctly
               formatted man page.  This defaults to the same value as
               $(ZSUFF).

In addition to these macros, the common.mk file defines default rules to
do the following:

- Convert man page source files contained in files with a ".man" extension
  into ASCII plaintext files having the $(MANSUFF) extension.
- Convert man page source files contained in files with a ".man" extension
  into ASCII plaintext files having the ".doc" extension.
- Convert man page source files contained in files with a ".man" extension
  into PostScript source code (with a ".ps" extension) suitable for printing.

Each of the components' makefiles also include the rules.mk file, which
contains the following targets:

all -- A place-holder to make "all" the default target when "make"
       is invoked with no command line arguments.
installLib -- Provides the recipe for installing libraries into the
              $(ROOT) directory structure.
installInclude -- Provides the recipe for installing public header
                  files into the $(ROOT) directory structure.
installDocs -- Provides the recipe for installing formatted man pages into
               the $(ROOT) directory structure.
everything -- Causes the targets "all" and "docs" to be built.  The "docs"
              target is defined in each component's makefile.
install -- Causes the targets "installInclude", "installLib", and
           "installDocs" to be built in that order.
clean -- Removes derived files from source directory, excluding the final
         product (public header files, libraries and documentation).
clobber -- Removes all derived files from source directory.  This target is
           also known by the following names:  spotless, realclean, and
           veryclean.
MANIFEST -- Produces the MANIFEST file, which lists all of the files that
            are distributed with each component.
gct -- In a spotless environment, instruments a component for coverage
       testing using GCT 1.2.  "make clobber" must be done after coverage
       testing is complete.

Each of the components' makefiles contain the following targets:

all -- Builds the component library and test case.  This must be
       default target that is built when "make" is invoked with no
       arguments.
docs -- Builds ASCII plaintext and PostScript documents.
installDocs -- Lists formatted man pages to be installed into the $(ROOT)
               directory structure.
installInclude -- Lists public header files to be installed into the $(ROOT)
                  directory structure.
installLib -- Lists libraries to be installed into the $(ROOT) directory
              structure.
test -- Builds the component's test case, which is a program named "test".

Following is a sample makefile for a component.  It assumes the existence of
the following files:

Makefile -- The makefile.
mycomp.c -- Source code implementing the sample component.
mycomp.h -- Public header file for the sample component.
mycomp.man -- Troff source code for the man page for the sample component.
mycomppriv.h -- Private header file used by the source files of the sample
                component.
README -- Information about the component.
test.c -- Source file for the component's test case.

----------------

# Pick up the standard macros and rules.

include ../../common.mk
include ../../rules.mk

# Specify the name of the component's library archive file.
TARGET = libmycomp.$(LIBSUFF)

# These are the object files that implement the sample component.  There
# should be one .o file listed here for each .c file contained in this
# source directory.
OBJECTS = mycomp.o

# Default target, library and test program
all:	$(TARGET) test

# Documentation
docs:	mycomp.ps mycomp.doc

# Install just the public header file using rules.mk
installInclude: mycomp.h

# Install the component's library archive file using rules.mk
installLib:	$(TARGET)

# Install the man page using rules.mk
installDocs:	mycomp.man

# This produces the library.  Should work for both System V and BSD.
$(TARGET): $(OBJECTS)
	$(AR) $@ `lorder $? | tsort`
	$(RANLIB) $@

# This produces the object code using default rules.
$(OBJECTS): mycomp.h mycomppriv.h

objects: $(OBJECTS)

# This produces the test program.
test:	test.o $(TARGET)
	$(LD) $(CFLAGS) $(LFLAGS) -o test test.o $(TARGET) -lchipset \
		$(GCTSTUFF) $(TESTLIBS)

# This produces the ASCII plaintext documentation using default rules.
mycomp.doc: mycomp.man

# This produces the PostScript documentation using default rules.
mycomp.ps: mycomp.man

### End of file ###

----------------

The developer is able to build and test a new component simply by invoking
"make" in the directory containing the component's source code.

Once a new component is written, a test program must be written to verify its
correctness.  This test case should try to maximize coverage.  Tools such as
gct (available from the Gnu Project) can help with this.  If the component
performs dynamic memory allocation, then several debugging malloc packages
are available from the comp.sources.* archives (e.g. Conor P. Cahill's
malloclib package or Brandon Allbery's malloc-debug package) that can help
sniff out misuses of dynamically allocated storage.  Commercial alternatives
such as Purify and Purecov (from Pure Software, Inc.) can also be used.

The test case is an executable file called "test", and should run without
command line parameters specified.  Any diagnostic output should be displayed
on standard output.  The test program must exit with a 0 status if it is
successful, or with a non-zero status if it fails.

After the component is written and tested in isolation, its installation
procedures can be tested by invoking "make install".  This installs the
relevant files into the $(INCDIR), $(LIBDIR), and $(MANDIR) directories as
appropriate.  Integration with the rest of the Software ChipSet is
accomplished by invoking "make" from the "chipset" directory, as described
above.  The new component can be installed on a live system by invoking
"make install" from the "chipset" directory.

In order for the new component to be distributed, the "MANIFEST" target must
be made in its source directory.  The contents of the MANIFEST file should
then be reviewed.  This notifies the build scaffolding that the component is
complete and eligible for further distribution if the new component is
included in the $(COMPONENTS) list (which is true by default).

New distributions of the Software ChipSet are made by making one of the
following targets in the "chipset" directory.  All of the distribution
files appear in the $(STAGEINST) directory.

shar -- Produces a Rich $alz multi-part sharchive.
cpio -- Produces a compressed portable cpio archive.
tar -- Produces a compressed tar archive.
zip -- Produces a zip archive.

