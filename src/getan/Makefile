CC=gcc -g -O0 -Wall
LIBS=-lncurses -lpanel -lgetan
OBJS=main.o file.o buffer_data.o display_buffer.o
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

