CC=gcc
LIBS=-lncurses -lgetan
OBJS=main.o
PROG=getan

CFLAGS=-I../.inc
LDFLAGS=-L../.lib

all: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
clean:
	rm -rf *.o $(PROG)

