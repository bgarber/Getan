CC=gcc -g -O0
LIBS=-lncurses -lgetan
OBJS=main.o
PROG=getan

CFLAGS=-I../core/include
LDFLAGS=-L../core/.lib

all: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
clean:
	rm -rf *.o $(PROG)

