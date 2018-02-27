#
# PROGRAM:	Assignment 6
# PROGRAMMER: 	VICTOR PADILLA
#

CC = g++
CCFLAGS = -Wall -std=c++11

Assign5: Assignment6.o
	$(CC) $(CCFLAGS) -o Assignment6 Assignment6.o

Assignment5.o: Assignment6.cpp
	$(CC) $(CCFLAGS) -c Assignment6.cpp

clean:
	-rm *.o
