DEPS = list.h
CFILES = listtest.c list.c
CFLAGS = -Wall -g -O1 -std=c11 -o

all: $(CFILES) $(DEPS) Makefile
	gcc $(CFLAGS) listtest listtest.c list.c

clean:
	rm -f listtest

