#
# Makefile
#
CC = gcc
CFLAGS += -Wall -Wunused -Wstrict-prototypes
#
# __for debugging__
# CFLAGS += -pipe -g -m486 -Wall -Werror -Wunused -Wstrict-prototypes


BIN = heat

all: main

winbond.o: winbond.c config.h
	$(CC) $(CFLAGS) -c winbond.c

main.o: main.c config.h
	$(CC) $(CFLAGS) -c main.c

main: main.o winbond.o
	$(CC) main.o winbond.o -o $(BIN)
	strip $(BIN)

clean:
	rm -f *.o $(BIN)

distclean:
	rm -f *.o $(BIN)

