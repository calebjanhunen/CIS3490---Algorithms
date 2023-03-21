CC = gcc
CFLAGS =  -Wall -std=c99 -pedantic 

all: P11


# FOR P11
P11: P11.o Q1_functions.o
	$(CC) $(CFLAGS) -g Q1_functions.o P11.o -o P11

P11.o: P11.c A4_header.h
	$(CC) $(CFLAGS) -g -c P11.c -o P11.o

Q1_functions.o: Q1_functions.c A4_header.h
	$(CC) $(CFLAGS) -g -c Q1_functions.c -o Q1_functions.o

# FOR P12
P12: P12.o Q1_functions.o
	$(CC) $(CFLAGS) -g Q1_functions.o P12.o -o P12

P12.o: P12.c A4_header.h
	$(CC) $(CFLAGS) -g -c P12.c -o P12.o

Q1_functions.o: Q1_functions.c A4_header.h
	$(CC) $(CFLAGS) -g -c Q1_functions.c -o Q1_functions.o


clean:
	rm *.o P11