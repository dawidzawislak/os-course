CXX=gcc
CFLAGS=-c -g -Wall

all: countdown

countdown.o: countdown.c
	$(CXX) $(CFLAGS) countdown.c

countdown: countdown.o
	$(CXX) countdown.o -o countdown

countdown_dbg: countdown.o
	$(CXX) countdown.o -o countdown

.PHONY: clean all
clean:
	rm *.o countdown