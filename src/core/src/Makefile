CC=gcc -g -O0 -Wall
AR=ar
OBJS=getan_buffer.o getan_buflist.o getan_filebuf.o
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

