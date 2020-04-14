# software-chipset

The Software ChipSet is a collection of reusable software components that
is being placed in the public domain by its author, Paul Sander.  The goal
of the Software ChipSet is to provide small, general, production quality
off-the-shelf solutions to common problems that are faced by programmers.
If compared to integrated circuits, these components probably best correspond
to standard cells.  The complexity of the components are comparable to SSI
(small-scale integration) and MSI (medium scale integration) devices, but
many of them are reentrant and can be composed into larger components.

The components that comprise the Software ChipSet are intended to be general
enough to be used in a wide variety of applications.  Two of the key features
of these components are generalized interfaces, and programmability.  The
generalized interfaces permit the components to be used with arbitrary data
types.  Programmability permits the application to tune the components to
its data types and performance requirements at run-time.  In addition, several
components solve similar problems with varying performance and storage
characteristics; in such cases, the interfaces of the components are identical,
save for their initial configuration.

The programmability feature of the components also allows them to be composed
into larger components.  The design of the components is such that components
buried deep in such a composition can still be configured by the application
in a controlled way.  In addition, such components can be easily swapped out
for others should the programmer find that to be desirable.

The components are designed to be portable across Unix platforms, but many
will port to other platforms easily.  The target audience is rather ambitious:
All platforms that support the standard Unix utilities, an have a standard
C compiler and have Gnu Make installed.

Components available include:
btree - In-memory B-tree implementation
dupkey - Generalizes in-memory unique key index structures (e.g. btree,
         list) to allow redundant keys
list - In-memory doubly-linked list
readln - "Safe" text line input, supporting lines of arbitrary length

Please send bug reports and other comments to Paul Sander via Internet mail
at paul@wakawaka.com

VERSIONS:

This is Software ChipSet release 1.5.1

This distribution contains:
- Build scaffolding 1.5.1
- Btree 2.15.1
- Dupkey 1.0.1
- List 1.5.1
- Readln 1.0.1

CHANGES since version 1.5.0:

- Removed obsolete MANIFEST files.

CHANGES since version 1.4.1:

- Modernized the Makefile system and improved its correctness.
- Removed support for older Make programs.  Gnu Make is now a requirement.
- Multi-rooted builds are now supported, replacing the staging directory.
- Removed all packaging methods except for tar.
- Removed support for GCT coverage analysis.
- Man page pre-formatting was removed.
- Removed manifest creation and verification.
- Rewrote the README.md, BUILD, and INSTALL files.
- Removed the old README file that was replaced by the README.md file.

CHANGES since version 1.4:

- Compiled the library for the first time since 1995 and fixed bitrot.
  Software ChipSet compiles and passes its test suite on the following
  systems:

>CentOS 8.1\
>FreeBSD 12.1\
>MacOSX 10.13.4\
>OpenIndiana 2019.10\
>Raspian 8\
>Ubuntu 18.04.1


CHANGES since version 1.3:
- Added the dupkey component.
- Brought the BUILD file up to date and included it in the distribution.

CHANGES since version 1.2:
- Added the readln component, which performs text line input from an
  arbitrary text stream safely without regard to line length.
- Changed build scaffold to handle ranlib differently.  Systems that don't
  have ranlib must now set the RANLIB macro in common.mk to /bin/true or
  some other no-op.
- The "verify" target in the top-level makefile now reads the COMPONENTS
  macro to determine what components to check.
- Repaired "rm *" problem in "make clobber" when man pages are not compressed.
- Modified the build scaffold to better abstract out the manner in which
  libraries are built.  It is now possible to use a different tool than ar
  to build libraries, which can have filename extensions other than ".a".
  This supports the building of shared libraries on some systems.
- Renamed the README file to INSTALL.
- Renamed the ChipSet file to README.
- Repaired compilation warnings in the dll_join function and the list
  test program.

CHANGES since version 1.1:

- Instructions displayed when unpacking sharchives were clarified.
- "make clobber" in the root directory no longer removes $(STAGE) because
  it might be the root of the source tree.
- "make tar" extended to pack directory structures.
- Gave a better default value of $(STAGE).
- Build scaffolding now supports an old version of GCT.
- Fixed memory leaks in BTREE.
- Minor man page edits in LIST.
- dll_new now accepts a null setup pointer and treats it the same as
  null comp and data pointers.

ACKNOWLEDGEMENTS:

I'd like to thank the following people who have pointed out legitimate
bugs in the code and made suggestions to improve it:

>Greg McFarlane\
George Velamparampil
