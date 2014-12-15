## $Id: makefile,v 1.6 2001/03/24 00:12:47 hal Exp $
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

LIBRARIES = string system ipc execute_elf memory unicode ipv4 \
video serial console random log file math checksum mutex pci time \
list sound

CFLAGS = -Wall -W -Wshadow -Wpointer-arith -Waggregate-return \
-Wstrict-prototypes -Wredundant-decls -Winline -Wmissing-prototypes \
-Werror -Wcast-align -Wbad-function-cast -Wsign-compare \
-Wmissing-declarations -Wmissing-noreturns -pipe \
-Wnested-externs -O3 -fno-builtin -funsigned-char -g

INCLUDES = -I$$CHAOS_INSTALL_PATH/data/programming/c/headers

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
	for e in $(LIBRARIES) ; do cd $$e && ./configure --install-prefix $$CHAOS_INSTALL_PATH || exit ; cd .. ; done

install:
	for e in $(LIBRARIES) ; do $(MAKE) -C $$e install || exit ; done
	mkdir -p $$CHAOS_INSTALL_PATH/data/programming/linker
	cp chaos.ld $$CHAOS_INSTALL_PATH/data/programming/linker
	mkdir -p $$CHAOS_INSTALL_PATH/data/programming/c/startup
	$(MAKE) startup.o
	cp startup.o $$CHAOS_INSTALL_PATH/data/programming/c/startup
