#
# PROGRAM:	Assignment 1
# PROGRAMMER: 	VICTOR PADILLA
#

CC = g++
CCFLAGS = -Wall -std=c++11

Assign2: Assignment1.o
	$(CC) $(CCFLAGS) -o Assignment1 Assignment1.o

Assignment2.o: Assignment1.cpp
	$(CC) $(CCFLAGS) -c Assignment1.cpp

clean:
	-rm *.o
