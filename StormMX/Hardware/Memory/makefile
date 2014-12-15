LIBRARIES = physical virtual

PREFIX=
STATIC_LIBRARY_PATH = 

DEFS = -DSTORM

CFLAGS = -W -Wshadow -Wpointer-arith -Waggregate-return \
-Wstrict-prototypes -Wredundant-decls -Winline -Wmissing-prototypes \
 -Wcast-align -Wbad-function-cast -Wsign-compare \
-Wmissing-declarations -Wmissing-noreturns -pipe \
-Wnested-externs -O3 -fno-builtin -funsigned-char -g

INCLUDES = \
-I. -I../../Include


CC = gcc
NASM = nasm
AR = ar
RANLIB = ranlib
GZIP = gzip -f

%.o: %.c
	$(CC) -o $(@) $(CFLAGS) $(INCLUDES) $(DEFS) -c $<

.PHONY: all


all:
	for e in $(LIBRARIES) ; do $(MAKE) -C $$e || exit ; done

rall:	clean 
	for e in $(LIBRARIES) ; do $(MAKE) -C $$e rall || exit ; done
