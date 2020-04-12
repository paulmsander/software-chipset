# Makefile -- This file contains instructions to build the doubly-linked
#             list implementation and its related files.  Edit this as
#             needed for your system.
#
# This file is part of a suite of programs called Software Chipset.
# The source code for Software Chipset has been released into the
# public domain by its author, Paul Sander.

# Declare this component.

COMPONENT = list
TARGET = $(LIBDIR)/libdlist.a

# Pick up the standard macros and rules.

include ../../rules.mk

# These are the public header files to be installed in the build tree.

HEADERS = dlist.h

# These are the object files that implement the doubly-linked list.

OBJECTS = dlsetup.o dlnew.o dldestroy.o dlinsutl.o dlinsert.o dldump.o \
	dldelutl.o dldelete.o dlutil.o dlsearch.o dltrav.o dlfirst.o dlnext.o \
	dllast.o dlprev.o dlrankutl.o dlrank.o dldelrank.o dldata.o dlpushf.o \
	dlpushr.o dlpush.o dlpopf.o dlpopr.o dlpop.o dlpeekf.o dlpeekr.o \
	dlpeek.o dljoin.o

# Documentation for the doubly-linked list.

MANPAGES = dlist.$(MANSECT)

# The chipset and list libraries depend on these objects.

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

## Miscellaneous
#TARGET = libdlist.$(LIBSUFF)
#
#
## Default target, library and test program
#all:	$(TARGET) test
#
## Documentation
#docs:	dlist.ps dlist.doc
#
## Install just the header file
#installInclude: dlist.h
#
## Install the library
#installLib: $(TARGET)
#
## Install the documentation
#installDocs: dlist.man
#
## This produces the library.  ranlib is desireable on BSD-derived systems.
#$(TARGET): $(OBJECTS)
#	$(AR) $@ $(OBJECTS)
#
## This produces the object code.
#$(OBJECTS): dlpriv.h dlist.h
#
#objects: $(OBJECTS)
#
## This produces the test program.
#test:   test.o $(TARGET)
#	$(CC) $(CFLAGS) $(LFLAGS) -o test test.o $(TARGET) $(GCTSTUFF) \
#		$(TESTLIBS)
#
## This produces the ASCII plaintext documentation.
#dlist.doc: dlist.man
#
## This produces the PostScript documentation.
#dlist.ps: dlist.man
#
#### End of file ###
#
