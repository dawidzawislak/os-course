CXX=gcc
CFLAGS=-c -Wall

main.o: main.c
	$(CXX) $(CFLAGS) main.c

myls: main.o
	$(CXX) main.o -o myls

all: myls

clean:
	rm myls *.o

.PHONY: all clean