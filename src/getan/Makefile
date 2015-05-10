CC=gcc
LIBS=-lncurses
OBJS=main.o
PROG=getan

CFLAGS=-I../core

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
clean:
	rm -rf *.o $(PROG)

