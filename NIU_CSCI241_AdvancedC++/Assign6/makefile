#
#  PROGRAM:   assign6
#  AUTHOR:    Victor Padilla
#  LOGON ID:  z1689628
#  DUE DATE:  11-6-2015
#
CC = g++
CCFLAGS = -Wall -O
ASSIGN = assign6
CLASS1 = Queue
	
$(ASSIGN) : $(ASSIGN).o $(CLASS1).o
	$(CC) $(CCFLAGS) -o $(ASSIGN) $(ASSIGN).o $(CLASS1).o -lm

$(CLASS1).o : $(CLASS1).cpp $(CLASS1).h
	$(CC) -c $(CCFLAGS) $(CLASS1).cpp

$(ASSIGN).o : $(ASSIGN).cpp $(CLASS1).h
	$(CC) -c $(CCFLAGS) $(ASSIGN).cpp

clean :
	- rm *.o
	- rm $(ASSIGN)
