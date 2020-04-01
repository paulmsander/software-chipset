# Makefile -- This file contains instructions to build the in-memory B-tree
#             implementation and its related files.  Edit this as needed
#             for your system.  This makefile works properly with brain-dead
#             SVR2 make, so it should work with your tool, too.

# This file is part of a suite of programs called Software Chipset.
# The source code for Software Chipset has been released into the
# public domain by its author, Paul Sander.

# Pick up the standard macros and rules.

include ../../common.mk
include ../../rules.mk

# Miscellaneous
TARGET = libbtree.$(LIBSUFF)

# These are the object files that implement the B-tree.
OBJECTS = btmalloc.o btutil.o bt_last.o bt_next.o bt_prev.o \
	btdelete.o btdestroy.o btdump.o btfirst.o btinsert.o btnew.o \
	btsearch.o bttraverse.o btrank.o btdelutl.o btdelrank.o btdata.o

# Default target, library and test program
all:	$(TARGET) test

# Documentation
docs:	btree.ps btree.doc

# Install just the header file
installInclude: btree.h

# Install the library
installLib:	$(TARGET)

# Install the documentation.
installDocs:	btree.man

# This produces the library.  Should work for both System V and BSD
$(TARGET): $(OBJECTS)
	$(AR) $@ $(OBJECTS)

# This produces the object code.
$(OBJECTS): btpriv.h

objects: $(OBJECTS)

# This produces the test program.
test:	test.o $(TARGET)
	$(CC) $(CFLAGS) $(LFLAGS) -o test test.o $(TARGET) $(GCTSTUFF) \
		$(TESTLIBS)

# This produces the ASCII plaintext documentation.
btree.doc: btree.man

# This produces the PostScript documentation.
btree.ps: btree.man

### End of file ###

