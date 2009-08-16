
# Package name and version number:
lib_name=posix
project_name = pure-$(lib_name)
version = 0.1
dist = $(project_name)-$(version)
target = $(project_name)

# Try to guess the installation prefix (this needs GNU make):
prefix = $(patsubst %/bin/pure,%,$(shell which pure 2>/dev/null))
ifeq ($(strip $(prefix)),)
# Fall back to /usr/local.
prefix = /usr/local
endif

# Installation goes into $(libdir)/pure, you can also set this directly
# instead of $(prefix).
libdir = $(prefix)/lib

# Try to guess the host system type.
host = $(shell ./config.guess)

# Platform-specific defaults, edit this as needed.
#PIC = -fPIC # uncomment for x86-64 compilation
DLL = .so
shared = -shared

# Take care of some common systems.
ifneq "$(findstring -mingw,$(host))" ""
# Windows
DLL = .dll
endif
ifneq "$(findstring -darwin,$(host))" ""
# OSX (untested)
DLL = .dylib
shared = -dynamiclib
endif
ifneq "$(findstring x86_64-,$(host))" ""
# 64 bit, needs -fPIC flag
PIC = -fPIC
endif

# Default CFLAGS are -g -O2, CPPFLAGS, LDFLAGS and LIBS are empty by default.
# These can be set from the command line as usual. Use CFLAGS, CPPFLAGS and
# LDFLAGS for compiler (-O etc.), preprocessor (-I etc.) and linker (-L etc.) 
# options, respectively. LIBS is to be used for additional libraries to be
# linked (-l etc.).

CFLAGS = -g -O2
 
FLAGS = $(CPPFLAGS) $(CFLAGS) $(PIC) $(LDFLAGS)

PUREFILES = socket.pure fork.pure posix.pure socket.pure.head socket.pure.tail \
posix.head
sources = $(PUREFILES) 
DISTFILES = COPYING Makefile README config.guess examples/*.pure socket.c \
wait.c socket.pure doc/$(project_name).html
DISTFILES = COPYING Makefile README config.guess examples/*.pure socket.c \
wait.c $(sources) doc/$(project_name).html 
INCLUDE_PATH = /usr/include
all : socket.pure fork.pure posix.so doc/$(target).html

socket.pure :
	pure-gen --interface extern  --namespace posix::socket \
                 --output socket.pure.tmp1 $(INCLUDE_PATH)/sys/socket.h
	cat posix.head socket.pure.head  socket.pure.tmp1 socket.pure.tail > socket.pure
	rm socket.pure.tmp1

fork.pure :
	pure-gen --interface extern --namespace posix::fork \
                 -s "(.*fork.*|.*sleep.*)" --output fork.pure $(INCLUDE_PATH)/unistd.h
	pure-gen --interface extern --namespace posix::fork \
                 -s "(.*wait.*)" --output fork.pure  --noclobber \
                 -fc-auto $(INCLUDE_PATH)/sys/wait.h

posix.so: socket.pure fork.pure
	gcc -shared -o posix.so socket.c 

clean: 
	rm -f socket.pure fork.pure posix.so wait.c *.aux *.log *.out \
              doc/*.pdf doc/*.tex doc/*.html doc/*.txt $(dist).tar.gz *~
	rm -rf $(dist)
# documentation (this needs docutils)

doc/$(target).txt: README $(sources)
	pure-doc $(sources) > $@

.PHONY: html tex pdf

html: doc/$(target).html
tex: doc/$(target).tex
pdf: doc/$(target).pdf

doc/%.html: doc/%.txt
	rst2html.py $< $@
doc/%.tex: doc/%.txt
	rst2latex.py $< $@

# This also requires that you have TeX installed.

doc/%.pdf: doc/%.tex
	pdflatex $<
	pdflatex $<
	rm -f *.aux *.log *.out


install:
	test -d "$(DESTDIR)$(libdir)/pure" || mkdir -p "$(DESTDIR)$(libdir)/pure"
	cp $(PUREFILES) $(lib_name)$(DLL) doc/$(project_name).html "$(DESTDIR)$(libdir)/pure"

uninstall:
	rm -f "$(DESTDIR)$(libdir)/pure/csv.pure" "$(DESTDIR)$(libdir)/pure/$(lib_name)$(DLL)" "$(DESTDIR)$(libdir)/pure/$(project_name).html"
	for f in $(PUREFILES); do rm -f "$(DESTDIR)$(libdir)/pure/$$f"; done

dist: doc/$(target).html
	rm -rf $(dist)
	mkdir $(dist) && mkdir $(dist)/examples && mkdir $(dist)/doc
	for x in $(DISTFILES); do ln -sf $$PWD/$$x $(dist)/$$x; done
	rm -f $(dist).tar.gz
	tar cfzh $(dist).tar.gz $(dist)
	rm -rf $(dist)
