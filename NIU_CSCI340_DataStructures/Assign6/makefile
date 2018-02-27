CC = g++


CCFLAGS = -Wall -std=c++11


assignment6: assignment5.o assignment6.o assignment6main.o

	$(CC) $(CCFLAGS) -o assignment6 assignment5.o assignment6.o assignment6main.o


assignment5.o: assignment5.cpp assign5.cpp assign5.h

	$(CC) $(CCFLAGS) -c assignment5.cpp


assignment6.o: assignment6.cc assign5.h assign5.cpp assignment6.h
	$(CC) $(CCFLAGS) -c assignment6.cc


assignment6main.o: assignment6main.cc assign5.h assign5.cpp assignment6.cc  assignment6.h

	$(CC) $(CCFLAGS) -c assignment6main.cc


clean:

	- rm *.o assignment6
