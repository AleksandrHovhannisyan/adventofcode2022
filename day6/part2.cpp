#include <iostream>
#include <fstream>
#include "day6.h"

// https://adventofcode.com/2022/day/6

int main() {
    std::ifstream inputFile;
    inputFile.open("./input.txt");
    std::string buffer { "" };
    std::getline(inputFile, buffer);
    auto answer = getNumCharactersToPacketMarker(buffer, 14);
    if (answer.has_value()) {
        std::cout << "Answer: " << *answer << std::endl;
    } else {
        std::cout << "No solution" << std::endl;
    }

    inputFile.close();
    return 0;
}
