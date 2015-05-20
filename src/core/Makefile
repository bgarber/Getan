CC=gcc -fPIC -shared
OBJS=buffers.o files.o
HEADERS=buffers.h files.h
TARGET=libgetan.so
LIBDIR=../.lib
INCDIR=../.inc

all: $(TARGET)
	mkdir -p $(LIBDIR)
	mkdir -p $(INCDIR)
	cp $(TARGET) $(LIBDIR)
	cp $(HEADERS) $(INCDIR)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -rf *.o *.so $(LIBDIR) $(INCDIR)

.PHONY: all clean

