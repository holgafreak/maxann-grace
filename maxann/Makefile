# Make for maxann
CC = cc -g
SOURCES = buro.c maxannealing.c principal.c quali.c
OBJS = buro.o maxannealing.o principal.o quali.o

all:	maxanneal gen

gen:	gen.c
	$(CC) -o gen gen.c


maxanneal:	$(OBJS)
	$(CC) -o maxanneal $(OBJS) -lm

.c.o:
	$(CC) -c $<

clean:
	rm -f *.o gen maxanneal *.scm *~


