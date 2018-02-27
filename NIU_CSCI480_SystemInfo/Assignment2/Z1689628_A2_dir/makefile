#
# PROGRAM:	Assignment 1
# PROGRAMMER: 	VICTOR PADILLA
#

CC = g++
CCFLAGS = -Wall -std=c++11

Assign2: Assignment2.o
	$(CC) $(CCFLAGS) -o Assignment2 Assignment2.o

Assignment2.o: Assignment2.cpp
	$(CC) $(CCFLAGS) -c Assignment2.cpp

clean:
	-rm *.o
