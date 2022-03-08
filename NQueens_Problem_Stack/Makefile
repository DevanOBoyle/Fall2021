CXX = g++
CXXFLAGS = -Wall

OBJECTS = nqueens.o

nqueens: $(OBJECTS)
		$(CXX) -g $(CXXFLAGS) -o nqueens nqueens.o

nqueens.o: nqueens.cpp
		$(CXX) -g $(CXXFLAGS) -c nqueens.cpp

clean:
		rm -f *.o
		rm nqueens
