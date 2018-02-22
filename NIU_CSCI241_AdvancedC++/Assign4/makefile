#
#  PROGRAM:   assign4
#  AUTHOR:    Victor Padilla
#  LOGON ID:  z1689628
#  DUE DATE:  10/15/15
#

CC = g++
CCFLAGS = -Wall

FILE = assign4
CLASS = Complex

$(FILE): $(FILE).o $(CLASS).o
	$(CC) $(CCFLAGS) -o $(FILE) $(FILE).o $(CLASS).o

$(FILE).o: $(FILE).cpp $(CLASS).h
	$(CC) $(CCFLAGS) -c $(FILE).cpp

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CC) $(CCFLAGS) -c $(CLASS).cpp

clean:
	- rm *.o $(FILE)
