# Makefile -- This file contains instructions to build the safe line input
#             implementation and its related files.  Edit this as needed
#             for your system.

# This file is part of a suite of programs called Software Chipset.
# The source code for Software Chipset has been released into the
# public domain by its author, Paul Sander.

# Declare this component.

COMPONENT = readln
TARGET = $(LIBDIR)/lib$(COMPONENT).a

# Pick up the standard macros and rules.

include ../../rules.mk

# These are the public header files to be installed in the build tree.

HEADERS = readln.h

# These are the object files that implement the input routines.

OBJECTS = xreadln.o freadln.o readln.o

# Documentation for the safe line input implementation.

MANPAGES = readln.$(MANSECT)

# The chipset and readln libraries depend on these objects.

$(TARGET) $(LIBCHIPSET): $(addprefix $(OBJDIR)/,$(OBJECTS))

# Phony top-level targets.

all includes test: $(addprefix $(INCDIR)/,$(HEADERS))
all libs test: $(TARGET)
all libs test: $(LIBCHIPSET)

# Compile and run the unit test.

$(TESTDIR)/test.o: test.c
$(TESTDIR)/test: $(TESTDIR)/test.o $(TARGET)

.PHONY: test
test: $(TESTDIR)/test
	$<

clean::
	rm -f $(TESTDIR)/test $(TESTDIR)/test.o $(TESTDIR)/*.o.d

# Copy the manpages.

all docs: $(addprefix $(MANDIR)/,$(MANPAGES))

# Default target, library and test program
#all:	$(TARGET) test
#
## Documentation
#docs:	readln.ps readln.doc
#
## Install just the header file
#installInclude: readln.h
#
## Install the library
#installLib:	$(TARGET)
#
## Install the documentation.
#installDocs:	readln.man
#
## This produces the library.  Should work for both System V and BSD
#$(TARGET): $(OBJECTS)
#	$(AR) $@ $(OBJECTS)
#
## This produces the object code.
#$(OBJECTS): readln.h
#
#objects: $(OBJECTS)
#
## This produces the test program.
#test:	test.o $(TARGET)
#	$(CC) $(CFLAGS) $(LFLAGS) -o test test.o $(TARGET) $(GCTSTUFF) \
#		$(TESTLIBS)
#
## This produces the ASCII plaintext documentation.
#readln.doc: readln.man
#
## This produces the PostScript documentation.
#readln.ps: readln.man
#
#### End of file ###
#
