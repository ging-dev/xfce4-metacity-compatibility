CC=gcc
CFLAGS=-w $(shell pkg-config --cflags gtk+-3.0 libxfconf-0 libwnck-3.0)
LDFLAGS=$(shell pkg-config --libs gtk+-3.0 libxfconf-0 libwnck-3.0)

run: main.c
	$(CC) $(CFLAGS) main.c -o metacity-compatibility $(LDFLAGS)

install:
	cp metacity-compatibility /usr/local/bin

uninstall:
	rm /usr/local/bin/metacity-compatibility
