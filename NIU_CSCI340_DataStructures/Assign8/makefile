#
#  PROGRAM:   assign8
#  AUTHOR:    Victor Padilla
#  LOGON ID:  z1689628
#  DUE DATE:  4/18/2016
#
CC = g++
CCFLAGS = -Wall -O
ASSIGN = assignment8main
CLASS1 = assignment8

$(ASSIGN) : $(ASSIGN).o $(CLASS1).o
	$(CC) $(CCFLAGS) -o $(ASSIGN) $(ASSIGN).o -lm

$(CLASS1).o : $(CLASS1).h
		$(CC) -c $(CCFLAGS) $(CLASS1).h

$(ASSIGN).o : $(ASSIGN).cc $(CLASS1).h
		$(CC) -c $(CCFLAGS) $(ASSIGN).cc

clean :
	- rm *.o
	- rm *.gch
	- rm $(ASSIGN)
