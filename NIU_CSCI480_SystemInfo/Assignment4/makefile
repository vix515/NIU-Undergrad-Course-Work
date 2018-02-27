#
# PROGRAM:	Assignment 4
# PROGRAMMER: 	VICTOR PADILLA
#

CC = g++
CCFLAGS = -Wall -std=c++11

Assign2: Assignment4.o
	$(CC) $(CCFLAGS) -o Assignment4 Assignment4.o

Assignment4.o: Assignment4.cpp
	$(CC) $(CCFLAGS) -c Assignment4.cpp

clean:
	-rm *.o
