CC = gcc

CFLAGS = -I$(INCDIR) -lncurses -lm

SRCDIR = ./src/
LIBDIR = ./lib/
INCDIR = ./include/

SOURCES = $(SRCDIR)*.c
LIBSOURCES = $(LIBDIR)*.c

all: rogue run clean

rogue:
	$(CC) $(SOURCES) $(LIBSOURCES) $(CFLAGS) -o $@

debug: CFLAGS += -g

debug: rogue;

run:
	./rogue out 2>error.txt

clean:
	rm rogue
