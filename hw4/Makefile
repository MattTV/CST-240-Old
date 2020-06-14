DEPS = None 
FILES = wchild rchild pecho
CFILES = wchild.c rchild.c pecho.c
CFLAGS = -Wall -g -O1 -std=c11 -o

all: $(FILES) $(CFILES) Makefile

wchild: wchild.c
	gcc $(CFLAGS) wchild wchild.c

rchild: rchild.c
	gcc $(CFLAGS) rchild rchild.c

pecho: pecho.c
	gcc $(CFLAGS) pecho pecho.c

clean:
	rm -f wchild
	rm -f rchild
	rm -f pecho
