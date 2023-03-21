CC = gcc
CFLAGS =  -Wall -std=c99 -pedantic 

all: P11


# FOR P11
P11: P11.o P11_functions.o
	$(CC) $(CFLAGS) -g P11_functions.o P11.o -o P11

P11.o: P11.c A4_header.h
	$(CC) $(CFLAGS) -g -c P11.c -o P11.o

P11_functions.o: P11_functions.c A4_header.h
	$(CC) $(CFLAGS) -g -c P11_functions.c -o P11_functions.o

# FOR P12
P12: P12.o P12_functions.o
	$(CC) $(CFLAGS) -g P12_functions.o P12.o -o P12

P12.o: P12.c A4_header.h
	$(CC) $(CFLAGS) -g -c P12.c -o P12.o

P12_functions.o: P12_functions.c A4_header.h
	$(CC) $(CFLAGS) -g -c P12_functions.c -o P12_functions.o


clean:
	rm *.o P11