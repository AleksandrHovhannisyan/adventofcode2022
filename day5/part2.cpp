#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>
#include "parser.h"

// https://adventofcode.com/2022/day/5#part2 

int main() {
    std::ifstream inputFile;
    inputFile.open("./input.txt");
    auto crateStacks = parseCrateStacks(inputFile);
    auto moveInstructions = parseMoveInstructions(inputFile);

    for (auto instruction : moveInstructions) {
        auto numCratesToMove = instruction.numCratesToMove;
        auto &sourceStack = crateStacks[instruction.sourceStackNumber - 1];
        auto &destinationStack = crateStacks[instruction.destinationStackNumber - 1];

        // Move the desired number of elements as a group from sourceStack to destinationStack
        destinationStack.insert(destinationStack.begin(), std::make_move_iterator(sourceStack.begin()), std::make_move_iterator(sourceStack.begin() + numCratesToMove));

        // Erase the moved elements from sourceStack
        sourceStack.erase(sourceStack.begin(), sourceStack.begin() + numCratesToMove);
    }

    std::string answer = std::accumulate(crateStacks.begin(), crateStacks.end(), std::string(),
            [](const std::string& answer, auto crateStack) {
            return answer + crateStack.front();
            });
    std::cout << "ANSWER: " << answer << std::endl;

    inputFile.close();
    return 0;
}

