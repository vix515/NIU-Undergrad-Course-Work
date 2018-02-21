#
# PROGRAM:    assign2
# PROGRAMMER: Victor Padilla
# LOGON ID:   Z1689528
# DATE DUE:   9/22/2015
#

# Compiler variables
CCFLAGS = -ansi -Wall -std=c++11

# Rule to link object code files to create executable file
assign2: assign2.o Seller.o SalesDB.o
	g++ $(CCFLAGS) -o assign2 assign2.o Seller.o SalesDB.o

# Rules to compile source code files to object code
assign2.o: assign2.cpp SalesDB.h
	g++ $(CCFLAGS) -c assign2.cpp

Seller.o: Seller.cpp Seller.h
	g++ $(CCFLAGS) -c Seller.cpp

SalesDB.o: SalesDB.cpp SalesDB.h
	g++ $(CCFLAGS) -c SalesDB.cpp

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o assign2
