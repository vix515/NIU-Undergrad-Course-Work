#
#  PROGRAM:   assign5
#  AUTHOR:    Victor
#  LOGON ID:  z1689628
#  DUE DATE:  10-27-2015
#
CC = g++
CCFLAGS = -Wall -O
ASSIGN = assign5
CLASS1 = Vector

$(ASSIGN) : $(ASSIGN).o $(CLASS1).o
	$(CC) $(CCFLAGS) -o $(ASSIGN) $(ASSIGN).o $(CLASS1).o -lm

$(CLASS1).o : $(CLASS1).cpp $(CLASS1).h
	$(CC) -c $(CCFLAGS) $(CLASS1).cpp

$(ASSIGN).o : $(ASSIGN).cpp $(CLASS1).h
	$(CC) -c $(CCFLAGS) $(ASSIGN).cpp

clean :
	- rm *.o
	- rm $(ASSIGN)
