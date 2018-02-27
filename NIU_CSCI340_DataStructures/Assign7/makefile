#
#  PROGRAM:   assign7
#  AUTHOR:    Victor Padilla
#  LOGON ID:  z1689628
#  DUE DATE:  2/22/16
#
CC = g++
CCFLAGS = -Wall -O
ASSIGN = assignment7
	
$(ASSIGN) : $(ASSIGN).o 
	$(CC) $(CCFLAGS) -o $(ASSIGN) $(ASSIGN).o -lm

$(ASSIGN).o : $(ASSIGN).cc
	$(CC) -c $(CCFLAGS) $(ASSIGN).cc

clean :
	- rm *.o
	- rm $(ASSIGN)

