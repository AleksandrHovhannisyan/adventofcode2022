CC = g++
CFLAGS = -std=c++20 -Wall

.PHONY: all clean

all: part1 part2

utils.o: ../utils.cpp ../utils.h
	${CC} ${CFLAGS} -c ../utils.cpp

parser.o: parser.h parser.cpp utils.o
	${CC} ${CFLAGS} -c parser.cpp utils.o

part1: part1.cpp utils.o parser.o
	$(CC) $(CFLAGS) -o part1 part1.cpp utils.o parser.o

part2: part2.cpp utils.o parser.o
	$(CC) $(CFLAGS) -o part2 part2.cpp utils.o parser.o

clean:
	rm -f part1 part2 parser.o utils.o
