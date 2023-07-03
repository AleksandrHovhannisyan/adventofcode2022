CC = g++
CFLAGS = -std=c++20 -Wall

.PHONY: all clean

all: part1 part2

utils.o: ../utils.cpp ../utils.h
	${CC} ${CFLAGS} -c ../utils.cpp

part1: part1.cpp utils.o
	$(CC) $(CFLAGS) -o part1 part1.cpp utils.o

part2: part2.cpp utils.o
	$(CC) $(CFLAGS) -o part2 part2.cpp utils.o

clean:
	rm -f part1 part2 utils.o
