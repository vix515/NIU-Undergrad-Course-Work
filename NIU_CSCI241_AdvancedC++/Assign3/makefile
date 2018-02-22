#
# PROGRAM:    assign3
# PROGRAMMER: Victor Padilla
# LOGON ID:   Z1689528
# DATE DUE:   9/29/2015
#

# Compiler variables
CCFLAGS = -ansi -Wall -std=c++11

# Rule to link object code files to create executable file
assign3: assign3.o Seller.o SalesDB.o
	g++ $(CCFLAGS) -o assign3 assign3.o Seller.o SalesDB.o

# Rules to compile source code files to object code
assign3.o: assign3.cpp SalesDB.h
	g++ $(CCFLAGS) -c assign3.cpp

Seller.o: Seller.cpp Seller.h
	g++ $(CCFLAGS) -c Seller.cpp

SalesDB.o: SalesDB.cpp SalesDB.h
	g++ $(CCFLAGS) -c SalesDB.cpp

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o assign3
