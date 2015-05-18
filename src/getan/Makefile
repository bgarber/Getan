CC=gcc
LIBS=-lncurses
OBJS=main.o
PROG=getan

CFLAGS=-I../core
LDFLAGS=-L../core

all: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
clean:
	rm -rf *.o $(PROG)

