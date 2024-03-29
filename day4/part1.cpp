#include <iostream>
#include <fstream>
#include <string>
#include <utility>  // pair

// https://adventofcode.com/2022/day/4

/* Returns true if the two pairs of start-end ranges are overlapping (one contains the other) */
bool areFullyOverlappingRanges(std::pair<int, int> range1, std::pair<int, int> range2) {
    auto firstRangeContainsSecond = range1.first <= range2.first && range1.second >= range2.second;
    auto secondRangeContainsFirst = range2.first <= range1.first && range2.second >= range1.second;
    return firstRangeContainsSecond || secondRangeContainsFirst;
}

/* Returns a pair of start and end points defining a range */
std::pair<int, int> getRange(std::string pairAsString, char rangeDelimiter = '-') {
    std::pair<int, int> range { };
    auto delimiterIndex = pairAsString.find(rangeDelimiter);
    auto start = pairAsString.substr(0, delimiterIndex);
    auto end = pairAsString.substr(delimiterIndex + 1);
    range.first = std::stoi(start);
    range.second = std::stoi(end);
    return range;
}

/* Returns a pair of assignment ranges (start and end) */
std::pair<std::pair<int, int>, std::pair<int, int>> getRangePairs(std::string assignment, char pairDelimiter = ',') {
    auto pairDelimiterIndex = assignment.find(pairDelimiter);
    auto firstAssignment = assignment.substr(0, pairDelimiterIndex);
    auto secondAssignment = assignment.substr(pairDelimiterIndex + 1);

    std::pair<int, int> firstRange(getRange(firstAssignment));
    std::pair<int, int> secondRange(getRange(secondAssignment));
    return std::pair(firstRange, secondRange);
}

/** Returns the number of overlapping ranges in the given input file */
unsigned int getNumOverlappingRanges(std::ifstream& inputFile) {
    int numOverlappingRanges { 0 };
    std::string assignment { "" };
    while (std::getline(inputFile, assignment)) {
        auto rangePairs = getRangePairs(assignment);
        if (areFullyOverlappingRanges(rangePairs.first, rangePairs.second)) {
            numOverlappingRanges++;
        }
    }
    return numOverlappingRanges;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("./input.txt");
    auto numOverlappingRanges = getNumOverlappingRanges(inputFile);
    std::cout << "Answer: " << numOverlappingRanges << std::endl;
    inputFile.close();
    return 0;
}
