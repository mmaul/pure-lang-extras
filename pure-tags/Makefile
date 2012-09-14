#### BEGIN project specific configuration
# library, projecte name and version number:
lib_name = tags
project_name = pure-$(lib_name)
version = "0.1"

#entries below can be blank - set as apropriate
#generated pure files * will be deleted by clean *
GENPUREFILES = 
#manually created pure files * will not be deleted by clean *
MANPUREFILES = tags.pure 
#pure code (will be installed)
PUREFILES = $(MANPUREFILES) $(GENPUREFILES)
#generated c files * will be deleted by clean *
GENCFILES = 
#manually created cfiles * will not be delete by clean *
MANCFILES = 
#all c files
CFILES = $(GENCFILES) $(MANCFILES)
#all source include source used only during build
SOURCEFILES = $(PUREFILES) $(CFILES) 
#all files to be included in a source release
DISTFILES = COPYING Makefile README config.guess examples/*.pure $(SOURCEFILES) \
 doc/$(project_name).html
dist = $(project_name)-$(version)
target = $(project_name)

# Default CFLAGS are -g -O2, CPPFLAGS, LDFLAGS and LIBS are empty by default.
# These can be set from the command line as usual. Use CFLAGS, CPPFLAGS and
# LDFLAGS for compiler (-O etc.), preprocessor (-I etc.) and linker (-L etc.) 
# options, respectively. LIBS is to be used for additional libraries to be
# linked (-l etc.).
INCLUDE_PATH = /usr/include
CFLAGS = -g -O2

# project specific build tasks should be located after all task below

#### END project specific configuration
#### standard targes , probable don't need to edit below here

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
FLAGS = $(CPPFLAGS) $(CFLAGS) $(PIC) $(LDFLAGS)

all :  doc/$(target).html

#### BEGIN project specific build tasks

#### END   project specific build tasks

#$(lib_name)$(DLL): $(CFILES)
#	gcc -shared -o $@ $<

clean: 
	rm -f $(lib_name)$(DLL) $(GENCFILES) *.aux *.log *.out \
              doc/*.pdf doc/*.tex doc/*.html doc/*.txt $(dist).tar.gz *~
	rm -rf $(dist)
# documentation (this needs docutils)

doc/$(target).txt: $(SOURCEFILES)
	pure-doc $< > $@
	cp README.md doc/README.txt
.PHONY: html tex pdf

html: doc/$(target).html
tex: doc/$(target).tex
pdf: doc/$(target).pdf

doc/%.html: doc/%.txt 
	rst2html.py $< $@
	rst2html.py doc/README.txt doc/README.html

doc/%.tex: doc/%.txt
	rst2latex.py $< $@

# This also requires that you have TeX installed.

doc/%.pdf: doc/%.tex
	pdflatex $<
	pdflatex $<
	rm -f *.aux *.log *.out
	mv ../$@ doc

install:
	test -d "$(DESTDIR)$(libdir)/pure" || mkdir -p "$(DESTDIR)$(libdir)/pure"
	cp $(PUREFILES)  doc/$(project_name).html "$(DESTDIR)$(libdir)/pure/docs"

uninstall:
	rm -f "$(DESTDIR)$(libdir)/pure/$(PUREFILES)" "$(DESTDIR)$(libdir)/pure/$(lib_name)$(DLL)" "$(DESTDIR)$(libdir)/pure/$(project_name).html"
	for f in $(PUREFILES); do rm -f "$(DESTDIR)$(libdir)/pure/$$f"; done

dist: doc/$(target).html
	rm -rf $(dist)
	mkdir $(dist) && mkdir $(dist)/examples && mkdir $(dist)/doc
	for x in $(DISTFILES); do ln -sf $$PWD/$$x $(dist)/$$x; done
	rm -f $(dist).tar.gz
	tar cfzh $(dist).tar.gz $(dist)
	rm -rf $(dist)
