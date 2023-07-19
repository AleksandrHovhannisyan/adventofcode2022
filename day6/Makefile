CC = g++
CFLAGS = -std=c++20 -Wall

.PHONY: all clean

all: part1 part2

utils.o: ../utils.cpp ../utils.h
	${CC} ${CFLAGS} -c ../utils.cpp

day6.o: day6.h day6.cpp
	$(CC) $(CFLAGS) -c day6.cpp

part1: part1.cpp utils.o day6.o
	$(CC) $(CFLAGS) -o part1 part1.cpp utils.o day6.o

part2: part2.cpp utils.o day6.o 
	$(CC) $(CFLAGS) -o part2 part2.cpp utils.o day6.o

clean:
	rm -f part1 part2 utils.o day6.o
