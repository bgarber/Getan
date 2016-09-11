CC=gcc -g -O0 -Wall
LIBS=-lncurses -lgetan
OBJS=file.o buffer.o display.o display_buffer.o main.o
PROG=getan

CFLAGS=-I../core/include
LDFLAGS=-L../core/.lib

all: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROG)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
clean:
	rm -rf *.o $(PROG)

