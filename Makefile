CC=gcc
CFLAGS=-fPIC -Wall -W
LDFLAGS=-shared -Wl,-soname,libfakeaccess.so
LDLIBS=-ldl

all: libfakeaccess.so

%.so: %.o Makefile
	$(CC) $(LDFLAGS) -o $@ $< $(LDLIBS)

clean:
	rm -f *.so *.o

install: all
	install libfakeaccess.so /usr/local/lib
	ldconfig
