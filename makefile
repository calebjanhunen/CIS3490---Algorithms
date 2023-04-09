# Name: Caleb Janhunen
# ID: 1090270
# Date: April 10, 2023
# Assignment Number: 5

CC = gcc
CFLAGS =  -Wall -std=c99 -pedantic -g

# Function files
P1_functions.o: P1_functions.c A5.h
	$(CC) $(CFLAGS) -c P1_functions.c -o P1_functions.o

P2_functions.o: P2_functions.c A5.h
	$(CC) $(CFLAGS) -c P2_functions.c -o P2_functions.o

# P11
P11: P11.o P1_functions.o 
	$(CC) $(CFLAGS) P11.o P1_functions.o -o P11 

P11.o: P11.c A5.h
	$(CC) $(CFLAGS) -c P11.c -o P11.o

# P12
P12: P12.o P1_functions.o 
	$(CC) $(CFLAGS) P12.o P1_functions.o -o P12 

P12.o: P12.c A5.h
	$(CC) $(CFLAGS) -c P12.c -o P12.o

# P21
P21: P21.o P2_functions.o 
	$(CC) $(CFLAGS) P21.o P2_functions.o -o P21 

P21.o: P21.c A5.h
	$(CC) $(CFLAGS) -c P21.c -o P21.o

# P22
P22: P22.o P2_functions.o 
	$(CC) $(CFLAGS) P22.o P2_functions.o -o P22 

P22.o: P22.c A5.h
	$(CC) $(CFLAGS) -c P22.c -o P22.o

clean:
	rm *.o P11 P12 P21 P22