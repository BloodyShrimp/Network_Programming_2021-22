# Makefile

CC		:= gcc
CFLAGS	:= -Wall -std=c99 -pedantic -o
LDFLAGS	:= -s -o
LDLIBS	:= -L. -lmythread -lrt
DYNLIB	:= -Wl,-rpath ./

.PHONY: all clean cleano

all: 1.x 2.x 3.x 4.x 6.x 7.x 8.x

%.x: %.o
	$(CC) $(LDFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $@ $<

%.x: %.c
	$(CC) $(CFLAGS) $@ $^

clean:
	$(RM) *.o *.x *.a *.so

cleano:
	$(RM) *.o

1.x: 1.c
2.x: 2.c
3.x: 3.c
4.x: 4.c
6.x: 6.c
7.x: 7.c
8.x: 8.c