CC = gcc
CFLAGS =  -Wall -std=c99 -pedantic 

all: P11

P11: P11.c
	$(CC) $(CFLAGS) -g -o P11 P11.c

clean:
	rm P11