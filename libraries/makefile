## $Id: makefile,v 1.3 2000/10/10 20:04:13 plundis Exp $
## Authors: Henrik Hallin <hal@chaosdev.org>
##          Per Lundberg <plundis@chaosdev.org>

## Copyright 1999-2000 chaos development.

## This library is free software; you can redistribute it and/or
## modify it under the terms of the GNU Lesser General Public License
## as published by the Free Software Foundation; either version 2 of
## the License, or (at your option) any later version.

## This library is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## Lesser General Public License for more details.

## You should have received a copy of the GNU Lesser General Public
## License along with this library; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
## USA. 

LIBRARIES = string system ipc execute_elf memory unicode network \
video serial console random log file math checksum mutex iso pci time \
list sound

# Specify where you want make install to put the files in here. Remember to
# do a make configure afterwards!

PREFIX = /mnt/chaos

CFLAGS = -Wall -W -Wshadow -Wpointer-arith -Waggregate-return \
-Wstrict-prototypes -Wredundant-decls -Winline -Wmissing-prototypes \
-Werror -Wcast-align -Wbad-function-cast -Wsign-compare \
-Wmissing-declarations -Wmissing-noreturns -pipe \
-Wnested-externs -O3 -fno-builtin -funsigned-char -g

INCLUDES = -I$(PREFIX)/data/programming/c/headers

%.o: %.c
	$(CC) -o $(@) $(CFLAGS) $(INCLUDES) $(DEFS) -c $<

.PHONY: all autochaos clean config install

all:
	for e in $(LIBRARIES) ; do $(MAKE) -C $$e || exit ; done
	$(MAKE) startup.o

clean:
	for e in $(LIBRARIES) ; do $(MAKE) -C $$e clean || exit ; done
	rm -f startup.o

autochaos:
	for e in $(LIBRARIES) ; do cd $$e && pwd && autochaos || exit ; cd .. ; done

configure:
	for e in $(LIBRARIES) ; do cd $$e && ./configure --install-prefix $(PREFIX) || exit ; cd .. ; done

install:
	for e in $(LIBRARIES) ; do $(MAKE) -C $$e install || exit ; done
	mkdir -p $(PREFIX)/data/programming/linker
	cp chaos.ld $(PREFIX)/data/programming/linker
	mkdir -p $(PREFIX)/data/programming/c/startup
	$(MAKE) startup.o
	cp startup.o $(PREFIX)/data/programming/c/startup
	for e in $(LIBRARIES) ; do $(MAKE) -C $$e install || exit clean ; done
