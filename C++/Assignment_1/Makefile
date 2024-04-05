CXX      := g++
CXXFLAGS := -W -Wall -Wextra -std=c++20
TARGET   := assignment1
SRCS     := assignment1.cc
OBJS     := $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS)
