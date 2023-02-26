CC = gcc
CFLAGS =  -Wall -std=c99 -pedantic 

P11: P11.c
	$(CC) $(CFLAGS) -o P11 P11.c

P12: P12.c
	$(CC) $(CFLAGS) -o P12 P12.c

clean:
	rm P11 P12