# Makefile -- This file contains instructions to build the duplicate key
#             index implementation and its related files.  Edit this as
#             needed for your system.  This makefile works properly with
#             brain-dead SVR2 make, so it should work with your tool, too.

# This file is part of a suite of programs called Software Chipset.
# The source code for Software Chipset has been released into the
# public domain by its author, Paul Sander.

# Pick up the standard macros and rules.

include ../../common.mk
include ../../rules.mk

# Miscellaneous
TARGET = libdupkey.$(LIBSUFF)

# These are the object files that implement the redundant key index.
OBJECTS = dkdestroy.o dknew.o dkcompare.o dkinsert.o dksetup.o dkdump.o \
	dkbtree.o dklist.o dkfirst.o dklast.o dksearch.o dknext.o dkprev.o \
	dktraverse.o dkdelfirst.o dkdellast.o dkdellist.o dkdata.o

# Default target, library and test program
all:	$(TARGET) test

# Documentation
docs:	dupkey.ps dupkey.doc

# Install the header files
installInclude: dupkey.h

# Install the library and header file
installLib:     $(TARGET)

# Install the documentation.  You WILL want to modify this...
installDocs:    dupkey.man

# This produces the library.  ranlib is desireable on BSD-derived systems.
$(TARGET): $(OBJECTS)
	$(AR) $@ `lorder $? | tsort`
	$(RANLIB) $@

# This produces the object code.
$(OBJECTS): dkpriv.h dupkey.h

objects: $(OBJECTS)

# This produces the test program.
test:   test.o $(TARGET)
	$(LD) $(CFLAGS) $(LFLAGS) -o test test.o $(TARGET) -lchipset \
		$(GCTSTUFF) $(TESTLIBS)

# This produces the ASCII plaintext documentation.
dupkey.doc: dupkey.man

# This produces the PostScript documentation.
dupkey.ps: dupkey.man

### End of file ###

