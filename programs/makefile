## $Id: makefile,v 1.3 2000/10/15 21:15:31 plundis Exp $
## Author: Per Lundberg <plundis@chaosdev.org>

## Copyright 1999-2000 chaos development.

## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License as
## published by the Free Software Foundation; either version 2 of the
## License, or (at your option) any later version.

## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
## USA.

# List all the programs you want to compile here.

PROGRAMS = cluido # modplay tetris serialtest

# Specify where you want make install to put the files in here. Remember to
# do a make config afterwards!

PREFIX = /mnt/chaos

.PHONY: all autochaos clean config install tags

all:
	for e in $(PROGRAMS) ; do $(MAKE) -C $$e || exit ; done

clean:
	for e in $(PROGRAMS) ; do $(MAKE) -C $$e clean || exit ; done

autochaos:
	for e in $(PROGRAMS) ; do cd $$e && pwd && autochaos || exit ; cd .. ; done

configure:
	for e in $(PROGRAMS) ; do cd $$e && ./configure --install-prefix $(PREFIX) || exit ; cd .. ; done

install:
	for e in $(PROGRAMS) ; do $(MAKE) -C $$e install || exit clean ; done

tags:
	for e in $(PROGRAMS) ; do cd $$e ; etags *.[ch] ; cd .. ; done
