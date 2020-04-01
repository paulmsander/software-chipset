# Makefile -- This file contains instructions to build the safe line input
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
TARGET = libreadln.$(LIBSUFF)

# These are the object files that implement the input routines.
OBJECTS = xreadln.o freadln.o readln.o

# Default target, library and test program
all:	$(TARGET) test

# Documentation
docs:	readln.ps readln.doc

# Install just the header file
installInclude: readln.h

# Install the library
installLib:	$(TARGET)

# Install the documentation.
installDocs:	readln.man

# This produces the library.  Should work for both System V and BSD
$(TARGET): $(OBJECTS)
	$(AR) $@ $(OBJECTS)

# This produces the object code.
$(OBJECTS): readln.h

objects: $(OBJECTS)

# This produces the test program.
test:	test.o $(TARGET)
	$(CC) $(CFLAGS) $(LFLAGS) -o test test.o $(TARGET) $(GCTSTUFF) \
		$(TESTLIBS)

# This produces the ASCII plaintext documentation.
readln.doc: readln.man

# This produces the PostScript documentation.
readln.ps: readln.man

### End of file ###

