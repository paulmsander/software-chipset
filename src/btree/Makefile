# Makefile -- This file contains instructions to build the in-memory B-tree
#             implementation and its related files.  Edit this as needed
#             for your system.

# This file is part of a suite of programs called Software Chipset.
# The source code for Software Chipset has been released into the
# public domain by its author, Paul Sander.

# Declare this component.

COMPONENT = btree
TARGET = $(LIBDIR)/lib$(COMPONENT).a

# Pick up the standard macros and rules.

include ../../rules.mk

# These are the public header files to be installed in the build tree.

HEADERS = btree.h

# These are the object files that implement the B-tree.

OBJECTS = btmalloc.o btutil.o bt_last.o bt_next.o bt_prev.o \
	btdelete.o btdestroy.o btdump.o btfirst.o btinsert.o btnew.o \
	btsearch.o bttraverse.o btrank.o btdelutl.o btdelrank.o btdata.o

# Documentation for the B-tree.

MANPAGES = btree.$(MANSECT)

# The chipset and btree libraries depend on these objects.

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

## Default target, library and test program
#all:	$(TARGET) test
#
## Documentation
#docs:	btree.ps btree.doc
#
## Install just the header file
#installInclude: btree.h
#
## Install the library
#installLib:	$(TARGET)
#
## Install the documentation.
#installDocs:	btree.man
#
## This produces the library.  Should work for both System V and BSD
#$(TARGET): $(OBJECTS)
#	$(AR) $@ $(OBJECTS)
#
## This produces the object code.
#$(OBJECTS): btpriv.h
#
#objects: $(OBJECTS)
#
## This produces the test program.
#test:	test.o $(TARGET)
#	$(CC) $(CFLAGS) $(LFLAGS) -o test test.o $(TARGET) $(GCTSTUFF) \
#		$(TESTLIBS)
#
## This produces the ASCII plaintext documentation.
#btree.doc: btree.man
#
## This produces the PostScript documentation.
#btree.ps: btree.man
#
#### End of file ###
#
