DEPS = None 
FILES = wchild rchild
CFILES = wchild.c rchild.c
CFLAGS = -Wall -g -O1 -std=c11 -o

all: $(FILES) $(CFILES) Makefile

wchild: wchild.c
	gcc $(CFLAGS) wchild wchild.c

rchild: rchild.c
	gcc $(CFLAGS) rchild rchild.c

clean:
	rm -f wchild
	rm -f rchild
