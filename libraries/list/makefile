# This makefile was generated by autochaos 0.2.0. Please do not
# tamper with it unless you are very certain about what you are doing.

ALL_ARGUMENTS = --install-prefix /mnt/chaos 

PREFIX = /mnt/chaos
PACKAGE = list

# Compiler flags.

CFLAGS = -Wall -W -Wshadow -Wpointer-arith -Waggregate-return \
-Wstrict-prototypes -Wredundant-decls -Winline -Wmissing-prototypes \
-Werror -Wcast-align -Wbad-function-cast -Wmissing-noreturns -Wsign-compare \
-Wmissing-declarations -pipe \
-Wnested-externs -O3 -fno-builtin -funsigned-char -g $(EXTRA_CFLAGS) $(DEFINES)

INCLUDES = \
-I.. \
-I. -I$(PREFIX)/data/programming/c/headers

ALL_OBJECTS = \
./list.o

STATIC_LIBRARY_PATH = $(PREFIX)/data/programming/libraries/static

# Ideally, this would be -lwhatever, but we have not started patching
# the GNU tools yet...

LIBS = 

OBJECTS =  \
list.o


HEADERS =  \
functions.h \
list.h \
return_values.h \
types.h


SOURCES =  \
list.c

HEADER_PATH = $(PREFIX)/data/programming/c/headers/$(PACKAGE)/.

# TODO: Those should be overridable.

CC = gcc
NASM = nasm
AR = ar
RANLIB = ranlib
GZIP = gzip -f

%.o: %.c
	@echo Compiling $<...
	@$(CC) -o $(@) $(CFLAGS) $(INCLUDES) $(DEFS) -c $<
	@$(CC) -M $< $(CFLAGS) $(INCLUDES) $(DEFS) > $(*F).dep

%.o: %.S
	@echo Compiling $<...
	@$(CC) -o $(@) $(CFLAGS) $(INCLUDES) $(DEFS) -c $<
	@$(CC) -M $< $(CFLAGS) $(INCLUDES) $(DEFS) > $(*F).dep

%.o: %.asm
	$(NASM) -o $(@) $< -f elf

.PHONY: splash all clean install package-source

all: splash makefile library_list.a

clean: makefile
	rm -f library_list.a
	rm -f $(OBJECTS)
	rm -f *.dep
	-$(MAKE) clean-local
makefile: configure
	@./configure

splash:
	@echo -e "\n  Compiling library: list...\n"

configure: autochaos.rules
	@autochaos


LDFLAGS = $(PREFIX)/data/programming/c/startup/startup.o \
-nostdlib -Wl,-T,$(PREFIX)/data/programming/linker/chaos.ld -lgcc $(EXTRA_LDFLAGS)

library_list.a: $(OBJECTS)
	@echo "Creating library..."
	@$(AR) cru $(@) $(OBJECTS)
	@$(RANLIB) $(@)

install: all
	mkdir -p $(PREFIX)/data/programming/libraries/static
	cp library_list.a $(PREFIX)/data/programming/libraries/static
	mkdir -p $(PREFIX)/data/programming/c/headers/$(PACKAGE)
	for header in $(HEADERS) ; do cp $$header $(PREFIX)/data/programming/c/headers/$(PACKAGE) ; done

package-source:
	mkdir -p /root/Development/chaos/libraries/list/package-source/.
	-cp -f autochaos.rules changelog configure README AUTHORS TODO INSTALL /root/Development/chaos/libraries/list/package-source/.
	-cp -f makefile.template $(EXTRA_FILES) /root/Development/chaos/libraries/list/package-source/.
	for header in $(HEADERS) ; do cp $$header /root/Development/chaos/libraries/list/package-source/. ; done
	for source in $(SOURCES) ; do cp $$source /root/Development/chaos/libraries/list/package-source/. ; done
package-check: package-source
	     cd package-source && ./configure $(ALL_ARGUMENTS) && $(MAKE) && $(MAKE) clean
	     find package-source -name makefile -exec rm {} ';'
	     rm package-source/config.h
package: package-check
	rm -rf list-0.0.1
	mv package-source list-0.0.1
	tar cvIf list-0.0.1.tar.bz2 list-0.0.1
	     
-include list.dep

