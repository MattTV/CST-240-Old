DEPS = None 
FILES = wchild
CFILES = wchild.c
CFLAGS = -Wall -g -O1 -std=c11 -o

all: $(FILES) $(CFILES) Makefile

wchild: wchild.c
	gcc $(CFLAGS) wchild wchild.c

clean:
	rm -f wchild
	rm -f wchild.o
