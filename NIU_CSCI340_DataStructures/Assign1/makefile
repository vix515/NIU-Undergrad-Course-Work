#
#  PROGRAM:   assignment1
#  AUTHOR:    Victor Padilla
#  LOGON ID:  z1689628
#  DUE DATE:  2/1/2016
#
CC = g++
CCFLAGS = -Wall -O
ASSIGN = assignment1
CLASS1 = sorts
	
$(ASSIGN) : $(ASSIGN).o 
	$(CC) $(CCFLAGS) -o $(ASSIGN) $(ASSIGN).o -lm

$(ASSIGN).o : $(ASSIGN).cpp 
	$(CC) -c $(ASSIGN).cpp

clean :
	- rm *.o
	- rm $(ASSIGN)


