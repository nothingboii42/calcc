CC = gcc
CFLAGS = -Wall -Wextra -g

DESTDIR = /

all: calcc
calcc:
	$(CC) $(CFLAGS) -c main.c -o main.o
	$(CC) $(CFLAGS) main.o -o calcc

.PHONY: clean
clean:
	@rm -fv *.o
	@rm -fv calcc
	@rm -fv *.asm

install:
	@cp -fv calcc $(DESTDIR)/usr/bin
