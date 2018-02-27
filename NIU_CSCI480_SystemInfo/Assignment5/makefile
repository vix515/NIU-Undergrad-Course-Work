#
# PROGRAM:	Assignment 5
# PROGRAMMER: 	VICTOR PADILLA
#

CC = g++
CCFLAGS = -Wall -std=c++11

Assign5: Assignment5.o
	$(CC) $(CCFLAGS) -pthread -o Assignment5 Assignment5.o

Assignment5.o: Assignment5.cpp
	$(CC) $(CCFLAGS) -pthread -c Assignment5.cpp

clean:
	-rm *.o
