CC = gcc
CFLAGS =  -Wall -std=c99 -pedantic 

P11: P11.c
	$(CC) $(CFLAGS) -o P11 P11.c

P12: P12.c
	$(CC) $(CFLAGS) -o P12 P12.c
P21: P21.c
	$(CC) $(CFLAGS) -o P21 P21.c

clean:
	rm P11 P12 P21 P22