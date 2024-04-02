CXX=gcc
CFLAGS=-c -Wall

main.o: main.c
	$(CXX) $(CFLAGS) main.c

main2.o: main2.c
	$(CXX) $(CFLAGS) main2.c

process1: main.o
	$(CXX) main.o -o process1

process2: main2.o
	$(CXX) main2.o -o process2

all: process1 process2

clean:
	rm process1 process2 *.o

.PHONY: all clean