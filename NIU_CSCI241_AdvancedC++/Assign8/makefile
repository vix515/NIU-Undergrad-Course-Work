#
#  PROGRAM:   assign7
#  AUTHOR:    Victor Padilla
#  LOGON ID:  z1689628
#  DUE DATE:  11-7-2015
#
CC = g++
CCFLAGS = -Wall -O
ASSIGN = assign8
CLASS1 = sorts
	
$(ASSIGN) : $(ASSIGN).o 
	$(CC) $(CCFLAGS) -o $(ASSIGN) $(ASSIGN).o -lm

$(ASSIGN).o : $(ASSIGN).cpp 
	$(CC) -c $(ASSIGN).cpp

clean :
	- rm *.o
	- rm $(ASSIGN)

