CC=gcc -g -O0
AR=ar
OBJS=buffers.o files.o
TARGET=libgetan.a
LIBDIR=../.lib

CFLAGS=-I../include

all: $(TARGET)
	mkdir -p $(LIBDIR)
	cp $(TARGET) $(LIBDIR)

$(TARGET): $(OBJS)
	$(AR) rcs $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(TARGET) $(LIBDIR)

.PHONY: all clean

