CXX := g++
CXXFLAGS := -W -Wall -std=c++20

.PHONY: all clean

all: assignment2a assignment2b

assignment2a: assignment2a.cc
	$(CXX) $(CXXFLAGS) -o assignment2a assignment2a.cc

assignment2b: assignment2b.o portfolio.o
	$(CXX) $(CXXFLAGS) -o assignment2b assignment2b.o portfolio.o

assignment2b.o: assignment2b.cc
	$(CXX) $(CXXFLAGS) -c assignment2b.cc

portfolio.o: portfolio.cc
	$(CXX) $(CXXFLAGS) -c portfolio.cc

clean:
	rm -f assignment2a assignment2b *.o
