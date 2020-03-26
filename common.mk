# common.mk -- contains common make macros that are used the Makefiles
#              included with the Software ChipSet.  Please edit this file
#              as needed for your system.

# This file is part of a suite of programs called Software Chipset.
# The source code for Software Chipset has been released into the
# public domain by its author, Paul Sander.

SHELL=/bin/sh

################

# This is the default list of components that are built and installed,
# or installed into an archive when a new distribution is built.

#COMPONENTS=`/bin/ls ./src`
COMPONENTS=btree dupkey list readln

################

# The following macros describe the staging that is used when the top-level
# makefile builds the entire Software ChipSet distribution.  This staging
# area provides a means to test the all of the components while keeping
# them isolated from a live system.  All of these macros must specify
# fullpaths.  It would be a bad idea to put the staging area in the
# directory tree rooted at "`pwd`/src".

# STAGE is the root of a test staging area.  The full component library is
# built in the directory hierarchy rooted here, then installed into a
# live system from here.

STAGE=/tmp/ChipSet
#STAGE=/usr2/paul/tt/chipset/stage
#STAGE=$$HOME/work/chipset/stage

# The following macros specify where Software ChipSet public header files,
# libraries, and documentation go, and also specify working areas that are
# used when building the libraries and distribution media.  Each of these
# macros are used directly by the build procedures for the Software ChipSet.
# Note that these need not mirror the organization of the filesystem into
# which the component libraries are ultimately installed.

# Public header files go here.

STAGEINC=$(STAGE)/include

# Library archive files go here.

STAGELIB=$(STAGE)/lib

# Documentation goes here.

STAGEMAN=$(STAGE)/man

# Temporary work area.  This must be on the same physical device as
# the directory containing this file if new distributions of the Software
# ChipSet are made from your site.

STAGETMP=$(STAGE)/tmp

# Distribution media placed here.

STAGEINST=$(STAGE)/install


################

# The following macros describe the filesystem into which the Software
# ChipSet is ultimately installed.  This is the live system in general
# use.  All of these macros must specify fullpaths.

# This is where the components are installed for production use.

DEST=/usr/local
#DEST=/opt/local

# This is where public header files go.

DESTINC=$(DEST)/include

# This is where the libchipset.a file goes.

DESTLIB=$(DEST)/lib

# This is where the man pages are.  Software ChipSet man pages are
# installed in a man3 directory contained by this directory.

DESTMAN=$(DEST)/man


################

# The following macros are used to describe the development area in
# which components are built and tested in isolation from a live system.
# These macros are used by the individual makefiles within the component
# source directories themselves, and not by the top-level makefile that
# installs ALL of the components into a single staging area.  Though these
# macros need not have the same values as those for the staging area, they
# typically are out of convenience; this is because it allows a programmer
# to invoke "make" in each of the component source directories and at the
# top-level and get similar results.  Again, these must all be fullpaths.

# The root of the developer's installation area.  This is not used directly,
# but may be used to compute the locations of needed directories.

ROOT=$(STAGE)

# The location in which public header files are installed.

INCDIR=$(STAGEINC)

# The location in which component libraries are installed.

LIBDIR=$(STAGELIB)

# The location in which man pages are installed.

MANDIR=$(STAGEMAN)

################

# These are directives to the compiler and linker to specify search
# paths for needed files when components are built.

INCLUDES=-I$(INCDIR)
LIBSEARCH=-L$(LIBDIR)

################

# The following macros are used when the native C compiler is used.  The
# COVERAGE macro causes the components to write message to stdout that
# indicate decisions made.  This feature is useful for debugging the
# components, and should be turned off when the components are installed.

CC = cc $(INCLUDES)
CFLAGS = -O
#CFLAGS = -g -DCOVERAGE
#CFLAGS = -g
LD = cc $(LIBSEARCH)
LFLAGS =

# The following macros are used when the Gnu C compiler is used.

#CC = gcc $(INCLUDES)
#CFLAGS = -O -ansi -pedantic
#CFLAGS = -g -DCOVERAGE -ansi -pedantic
#CFLAGS = -g -ansi -pedantic
#LD = gcc $(LIBSEARCH)
#LFLAGS =

################

# This macro lists all of the special libraries with which the test programs
# must be linked.  Presently, none are really needed, but libmalloc often
# provides a better memory allocator than libc.a .

#TESTLIBS=
TESTLIBS=-lmalloc

################

# Manpage suffix after installation

MANSUFF=3l

################

# Set this to your ranlib program; must specify fullpath.  If you do not
# have ranlib, use /bin/true

#RANLIB=/bin/ranlib
RANLIB=/bin/true

################

# This is the command to create libraries.  Its first argument must be
# the name of the library, the rest must be the names of the .o files
# to be added.

AR=ar r
#AR=$(CC) -G -o

################

# This is the suffix of the library file.  .a is statically linkable
# library.

LIBSUFF=a
#LIBSUFF=so.1
################

# Set this appropriately to produce PostScript output.  Must be a filter.

#PSROFF=psroff -t -man
PSROFF=troff -Tpsc -man | psdit
#PSROFF=troff -Tpost -man

################

# Set this appropriately to produce ASCII plaintext.  Must be a filter.

NROFF=nroff -man | col -b -x
#NROFF=nroff -man

################

# This compresses ASCII plaintext files for some systems.  COMPRESS must
# be a filter.

COMPRESS=compress
ZSUFF=.Z
#COMPRESS=/bin/cat
#ZSUFF=

################

# These macros describe how man pages are processed prior to installation.
# Some systems prefer Troff source to be installed in /usr/man/whatever,
# while others prefer plaintext to be installed in /usr/catman/whatever.
# Still others want compressed plaintext.  And they figure out what type
# of file they have by looking at the file's extension.  So, INSTALLMAN
# specifies a filter that processes Troff source to produce the proper
# file for the "man" command, and INSTALLSUFF specifies the proper
# extension for the file after processing.  INSTALLSUFF is appended to
# MANSUFF when the man pages are processed.

INSTALLMAN=$(NROFF) | $(COMPRESS)
INSTALLSUFF=$(ZSUFF)

#INSTALLMAN=/bin/cat
#INSTALLSUFF=

################

# Default rules

.SUFFIXES: .$(MANSUFF) .man .doc .ps

# Format man pages

.man.$(MANSUFF):
	< $*.man $(NROFF) > $*.$(MANSUFF)

.man.doc:
	< $*.man $(NROFF) > $*.doc

.man.ps:
	< $*.man $(PSROFF) > $*.ps

################

# Default target, just in case

all:

### End of File ###

