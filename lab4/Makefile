CXX=gcc
CFLAGS=-c -Wall

1.o: 1.c
	$(CXX) $(CFLAGS) 1.c

zad1: 1.o
	$(CXX) 1.o -o zad1

catcher.o: catcher.c
	$(CXX) $(CFLAGS) catcher.c

catcher: catcher.o
	$(CXX) catcher.o -o catcher

sender.o: sender.c
	$(CXX) $(CFLAGS) sender.c

sender: sender.o
	$(CXX) sender.o -o sender

all: zad1 catcher sender

clean:
	rm zad1 catcher sender *.o

.PHONY: all clean