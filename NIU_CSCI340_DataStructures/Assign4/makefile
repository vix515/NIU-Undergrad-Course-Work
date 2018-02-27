#
#  PROGRAM:   assign4
#  AUTHOR:    Victor Padilla
#  LOGON ID:  z1689628
#  DUE DATE:  2/22/16
#
CC = g++
CCFLAGS = -Wall -O
ASSIGN = assignment4
CLASS1 = assign4
	
$(ASSIGN) : $(ASSIGN).o $(CLASS1).o
	$(CC) $(CCFLAGS) -o $(ASSIGN) $(ASSIGN).o $(CLASS1).o -lm

$(CLASS1).o : $(CLASS1).cpp $(CLASS1).h
	$(CC) -c $(CCFLAGS) $(CLASS1).cpp

$(ASSIGN).o : $(ASSIGN).cpp $(CLASS1).h
	$(CC) -c $(CCFLAGS) $(ASSIGN).cpp

clean :
	- rm *.o
	- rm $(ASSIGN)
