#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <numeric>
#include "parser.h"

int main() {
    std::ifstream inputFile;
    inputFile.open("./input.txt");
    auto crateStacks = parseCrateStacks(inputFile);
    auto moveInstructions = parseMoveInstructions(inputFile);

    for (auto instruction : moveInstructions) {
        auto &sourceStack = crateStacks[instruction.sourceStackNumber - 1];
        auto &destinationStack = crateStacks[instruction.destinationStackNumber - 1];

        for (auto i = 0; i < instruction.numCratesToMove; i++) {
            auto crateToMove = sourceStack.front();
            sourceStack.pop_front();
            destinationStack.push_front(crateToMove);
        }
    }

    std::string answer = std::accumulate(crateStacks.begin(), crateStacks.end(), std::string(),
            [](const std::string& answer, auto crateStack) {
            return answer + crateStack.front();
            });
    std::cout << "ANSWER: " << answer << std::endl;

    inputFile.close();
    return 0;
}
