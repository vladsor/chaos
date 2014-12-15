# $chaos: libraries.make,v 1.1 2002/06/21 08:01:02 per Exp $

# Abstract: Modules makefile
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.
# Use freely under the terms listed in the file COPYING.

# Settings.
# CC = i686-storm-chaos-gcc
INCLUDES = -I$(INSTALL_PATH)/data/programming/c/headers
EXTRA_CFLAGS = # -fPIC # Position-independant code.
CFLAGS = -Wall -W -Wshadow -Wpointer-arith -Waggregate-return \
-Wstrict-prototypes -Wredundant-decls -Winline -Wmissing-prototypes \
-Werror -Wcast-align -Wbad-function-cast -Wsign-compare \
-Wmissing-declarations -pipe -Wnested-externs \
-O3 -fno-builtin -funsigned-char -g -fomit-frame-pointer \
-ffreestanding $(EXTRA_CFLAGS) $(DEFINES) $(INCLUDES)
LDFLAGS = -nostdlib $(EXTRA_LDFLAGS)

# FIXME: Make it configurable.
INSTALL_PATH=/tftpboot

# Programs.
INSTALL = install

.PHONY: all clean install 

%.o: %.c
	$(CC) -c $< -o $(@) $(CFLAGS)
	@$(CC) -M $< $(CFLAGS) $(INCLUDES) $(DEFS) > $(*F).dep

%.o: %.S
	$(CC) -c $< -o $(@) $(CFLAGS)
	@$(CC) -M $< $(CFLAGS) $(INCLUDES) $(DEFS) > $(*F).dep

-include $(shell echo *.dep)
