CC=g++

CFLAGS=-Wsign-conversion -Werror -Wall -Wextra -std=c++20

all: assignment3 try_catch is_floating

assignment3: assignment3.o matrix_operations.o logging.o matrix.h
	$(CC) $(CFLAGS) -o assignment3 assignment3.o matrix_operations.o logging.o

assignment3.o:assignment3.cc matrix.h
	$(CC) $(CFLAGS) -c assignment3.cc 

matrix_operations.o:matrix_operations.cc matrix_operations.h matrix.h
	$(CC) $(CFLAGS) -c matrix_operations.cc

logging.o:logging.cc logging.h
	$(CC) $(CFLAGS) -c logging.cc

is_floating: is_floating.cc
	$(CC) $(CFLAGS) -o is_floating is_floating.cc

try_catch: try_catch.cc
	$(CC) $(CFLAGS) -o try_catch try_catch.cc

clean:
	-rm -f *.o assignment3 try_catch is_floating
