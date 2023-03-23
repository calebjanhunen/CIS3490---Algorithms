CC = gcc
CFLAGS =  -Wall -std=c99 -pedantic 

all: P11 P12 P2

# Function files
Q1_functions.o: Q1_functions.c A4_header.h
	$(CC) $(CFLAGS) -g -c Q1_functions.c -o Q1_functions.o

Q2_functions.o: Q2_functions.c A4_header.h
	$(CC) $(CFLAGS) -g -c Q2_functions.c -o Q2_functions.o

# FOR P11
P11: P11.o Q1_functions.o
	$(CC) $(CFLAGS) -g Q1_functions.o P11.o -o P11

P11.o: P11.c A4_header.h
	$(CC) $(CFLAGS) -g -c P11.c -o P11.o

# FOR P12
P12: P12.o Q1_functions.o
	$(CC) $(CFLAGS) -g Q1_functions.o P12.o -o P12

P12.o: P12.c A4_header.h
	$(CC) $(CFLAGS) -g -c P12.c -o P12.o

# For P2
P2: P2.o Q2_functions.o
	$(CC) $(CFLAGS) -g Q2_functions.o P2.o -o P2

P2.o: P2.c A4_header.h
	$(CC) $(CFLAGS) -g -c P2.c -o P2.o


clean:
	rm *.o P11 P12 P2