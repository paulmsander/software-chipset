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
the contents of the build root and onto a live system, and more instructions
to for building archives that can be used to distribute copies of the
components.

These four parts work together to provide a flexible environment in which
a developer can build and test new components in several contexts.  The
developer is able to invoke "make" in each component source directory for
testing purposes.  Once a component works in isolation, it can then be tested
with the entire Software ChipSet by compiling it into a build tree,, which
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
maintains a build tree in which derived artifacts are stored for testing.
When the Software ChipSet is installed onto a live system, the installed
files are copied from this build tree.  The build tree has the following
structure:

	buildroot
	  include
	  lib
	  man
	    man3
	  obj

The "buildroot" directory is the root directory of the build tree, and is
the same as the root of the source tree by default.  The "include" directory
contains public header files provided by each component, that are #include'd
by client applications.  The "lib" directory contains individual component
libraries and the libchipset.a library (which contains the sum of all of the
code and data contained by the other .a files contained in that directory).
The "man/man3" directory contains man pages (in nroff -man format).  The
"obj" directory contains compiled object files that derive the component
and chipset libraries.

A top-level build copies header and man page files, compiles C source to
object files, and derives archive libraries.  These are all stored in the
build root.  In a multi-root build, the source tree is left untouched and
may be read-only.

A component's makefile may contain other targets that are incidental to the
building of the above targets.

Each of the components' makefiles include the rules.mk file, which
contains pattern rules and phony top-level targets to compile and build
the component and chipset libraries.

all -- A place-holder to make "all" the default target when "make"
       is invoked with no command line arguments.
clean -- Removes derived files from source directory, excluding the final
         product (public header files, libraries and documentation).

Each of the components' makefiles contain the following targets:

all -- Builds the component library.  This must be default target that
       is built when "make" is invoked with no arguments.
clean -- Removes derived files created while building the component library.
docs -- Copies man pages to the build tree.
includes -- Copies header files to the build tree.
libs -- Builds the component library and adds the component to the
        chipset library in the build tree.
test -- Builds and runsthe component's test case, which is a program named
        "test".

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

# Declare the component.

COMPONENT = mycomp
TARGET = $(LIBDIR)/lib$(COMPONENT).a

# Pick up the standard macros and rules.

include ../../rules.mk

# These are the public header files to be installed in the build area.

HEADERS = mycomp.h

# These are the object files that implement the sample component.  There
# should be one .o file listed here for each .c file contained in this
# source directory.

OBJECTS = mycomp.o

# Documentation for the component.

MANPAGES = mycomp.$(MANSECT)

# The chipset and mycomp libraries depend on these objects.

$(TARGET) $(LIBCHIPSET): $(addprefix $(OBJDIR)/,$(OBJECTS))

# Phony top-level targets.

all includes test: $(addprefix $(INCDIR)/,$(HEADERS))
all libs test: $(TARGET)
all libs test: $(LIBCHIPSET)

# Compile and run the unit test.

$(TESTDIR)/test.o: test.c
$(TESTDIR)/test: $(TESTDIR)/test.o $(TARGET)

.PHONY test
test: $(TESTDIR)/test
	$<

# Clean the unit test program from the build tree.

clean::
	rm -f $(TESTDIR)/test $(TESTDIR)/test.o $(TESTDIR)/*.o.d

# Copy the man pages.

all docs: $(addprefix $(MANDIR)/,$(MANPAGES))

----------------

The developer is able to build and test a new component simply by invoking
"make" in the directory containing the component's source code.

Once a new component is written, a test program must be written to verify its
correctness.  This test case should try to maximize coverage.

The test case is an executable file called "test", and should run in the
build tree without command line parameters specified.  Any diagnostic output
should be displayed on standard output.  The test program must exit with a 0
status if it is successful, or with a non-zero status if it fails.

Integration with the rest of the Software ChipSet is accomplished by invoking
"make all" from the "chipset" directory, as described above.  The new
component can be installed on a live system by invoking "make install" from
the "chipset" directory.

New distributions of the Software ChipSet are made by making one of the
following targets in the "chipset" directory.  All of the distribution
files appear in the root of the build tree.

tar -- Produces a compressed tar archive.

