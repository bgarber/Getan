CC=gcc
OBJS=buffers.o files.o

all: $(OBJS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -rf *.o

.PHONY: all clean

