# Makefile -- This file contains instructions to build the duplicate key
#             index implementation and its related files.  Edit this as
#             needed for your system.

# This file is part of a suite of programs called Software Chipset.
# The source code for Software Chipset has been released into the
# public domain by its author, Paul Sander.

# Declare this component.

COMPONENT = dupkey
TARGET = $(LIBDIR)/lib$(COMPONENT).a

# Pick up the standard macros and rules.

include ../../rules.mk

# These are the public header files to be installed in the build tree.

HEADERS = dupkey.h

# These are the object files that implement the redundant key index.

OBJECTS = dkdestroy.o dknew.o dkcompare.o dkinsert.o dksetup.o dkdump.o \
	dkbtree.o dklist.o dkfirst.o dklast.o dksearch.o dknext.o dkprev.o \
	dktraverse.o dkdelfirst.o dkdellast.o dkdellist.o dkdata.o

# Documentation for the duplicate key index.

MANPAGES = dupkey.$(MANSECT)

# The chipset and dupkey libraries depend on these objects.

$(TARGET) $(LIBCHIPSET): $(addprefix $(OBJDIR)/,$(OBJECTS))

# Phony top-level targets.

all includes test: $(addprefix $(INCDIR)/,$(HEADERS))
all libs test: $(TARGET)
all libs test: $(LIBCHIPSET)

# Compile and run the unit test.

$(TESTDIR)/test.o: test.c
$(TESTDIR)/test: $(TESTDIR)/test.o $(TARGET) $(LIBCHIPSET)

.PHONY: test
test: $(TESTDIR)/test
	$<

clean::
	rm -f $(TESTDIR)/test $(TESTDIR)/test.o $(TESTDIR)/*.o.d

# Copy the manpages.

all docs: $(addprefix $(MANDIR)/,$(MANPAGES))

## Default target, library and test program
#all:	$(TARGET) test
#
## Documentation
#docs:	dupkey.ps dupkey.doc
#
## Install the header files
#installInclude: dupkey.h
#
## Install the library and header file
#installLib:     $(TARGET)
#
## Install the documentation.  You WILL want to modify this...
#installDocs:    dupkey.man
#
## This produces the library.  ranlib is desireable on BSD-derived systems.
#$(TARGET): $(OBJECTS)
#	$(AR) $@ $(OBJECTS)
#
## This produces the object code.
#$(OBJECTS): dkpriv.h dupkey.h
#
#objects: $(OBJECTS)
#
## This produces the test program.
#test:   test.o $(TARGET)
#	$(LD) $(CFLAGS) $(LFLAGS) -o test test.o $(TARGET) -lchipset \
#		$(GCTSTUFF) $(TESTLIBS)
#
## This produces the ASCII plaintext documentation.
#dupkey.doc: dupkey.man
#
## This produces the PostScript documentation.
#dupkey.ps: dupkey.man
#
#### End of file ###
#
