# Makefile

CC		:= gcc
CFLAGS	:= -Wall -std=c99 -pedantic -o
LDFLAGS	:= -s -o
LDLIBS	:= -L. -lmythread -lrt
DYNLIB	:= -Wl,-rpath ./

.PHONY: all clean cleano

all: server.x client.x

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

server.x: server.c
client.x: client.c