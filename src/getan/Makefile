CC=gcc
LIBS=-lncurses
OBJS=main.o
PROG=getan

all: $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(PROG)

%.o: %.c
	$(CC) -c $< -o $@

.PHONY:
clean:
	rm -rf *.o $(PROG)

