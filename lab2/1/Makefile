CXX=gcc
CFLAGS=-c -Wall

main.o: main.c
	$(CXX) $(CFLAGS) -c main.c

reverse: main.o
	$(CXX) main.o -o reverse

all: reverse

clean:
	rm reverse *.o

.PHONY: all clean