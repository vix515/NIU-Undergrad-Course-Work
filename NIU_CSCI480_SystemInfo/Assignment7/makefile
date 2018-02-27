#
# PROGRAM:	Assignment 7
# PROGRAMMER: 	VICTOR PADILLA
#

CC = g++
CCFLAGS = -Wall -std=c++11

Assign5: Assignment7.o
	$(CC) $(CCFLAGS) -o Assignment7 Assignment7.o

Assignment5.o: Assignment7.cpp
	$(CC) $(CCFLAGS) -c Assignment7.cpp

clean:
	-rm *.o
