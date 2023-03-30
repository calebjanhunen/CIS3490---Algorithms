# Name: Caleb Janhunen
# ID: 1090270
# Date: April 10, 2023
# Assignment Number: 5

CC = gcc
CFLAGS =  -Wall -std=c99 -pedantic -g

# Function files
P1_functions.o: P1_functions.c A5.h
	$(CC) $(CFLAGS) -c P1_functions.c -o P1_functions.o

# P11
P11: P11.o P1_functions.o 
	$(CC) $(CFLAGS) P11.o P1_functions.o -o P11 

P11.o: P11.c A5.h
	$(CC) $(CFLAGS) -c P11.c -o P11.o

clean:
	rm *.o P11