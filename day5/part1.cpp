#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <numeric>
#include "../utils.h"

int ITEM_CHAR_CODE_START = static_cast<int>('A');
int ITEM_CHAR_CODE_END = static_cast<int>('Z');

std::vector<std::deque<char>> parseCrateStacks(std::ifstream& inputFile) {
    std::string inputLine { "" };
    std::vector<std::deque<char>> crateStacks;
    int numCrateStacks { 0 };

    while(std::getline(inputFile, inputLine)) {
        // When reading first line, allocate space for stacks
        if (numCrateStacks == 0) {
            /* Preallocate a vector of vectors from the first line of input, using the following known facts:
             *
             * 1. Only one character is used to represent a crate (e.g., X, Y, or Z).
             * 2. If a crate is present, it is of the form: [X] (three characters).
             * 3. One whitespace character between crates on a single row.
             * 
             * Let n be the number of stacks. Then the total number of characters on a line is 3n + n - 1 = 4n - 1.
             * So to get the number of stacks (unknown) from the number of characters on a line (known), we do (line.length + 1) / 4
             *
             * NOTE: There is a line of input at the very end of all the crates that has all the stack numbers, but this approach allows us
             * to avoid having to find and read that line first. However, this is more prone to breaking if future crates can have more than 1 char.
             */
            numCrateStacks = (inputLine.length() + 1) / 4;
            for (int i = 0; i < numCrateStacks; i++) {
                crateStacks.push_back(std::deque<char>());
            }
        }

        bool isDoneParsing = false;
        // Read crates in the current line of input by "stack"
        for (int crateStackIndex = 0; crateStackIndex < numCrateStacks; crateStackIndex++) {
            // See logic above
            auto crateIndex = 4 * crateStackIndex + 1;
            auto crate = inputLine[crateIndex];
            auto crateCharCode = static_cast<int>(crate);

            // Valid crate symbol
            if (crateCharCode >= ITEM_CHAR_CODE_START && crateCharCode <= ITEM_CHAR_CODE_END) {
                // std::cout << "Pushing " << crate << " onto stack " << crateStackIndex + 1 << "\n";
                crateStacks[crateStackIndex].push_back(crate);
            } 
            // Spaces denote empty crates. Note that this is not super resilient. By coincidence we could hit a space on a different line.
            else if (crate != ' ') {
                isDoneParsing = true;
                break;
            }
        }

        if (isDoneParsing) {
            // We finished processing the stacks and reached the line with stack numbers.
            // Consume next blank line of input to prepare for next stage of parsing and break out.
            std::getline(inputFile, inputLine);
            break;
        }
    }

    return crateStacks;
}

struct MoveInstruction {
    int numCratesToMove;
    int sourceStackNumber;
    int destinationStackNumber;
};

// NOTE: It would be more performant to just do the stack manipulations while we're parsing the instructions,
// but I think it's nice to split up the tasks by 1) parsing first, and 2) solving after all parsing
std::vector<MoveInstruction> parseMoveInstructions(std::ifstream& inputFile) {
    std::string inputLine { "" };
    std::vector<MoveInstruction> moveInstructions { };

    while(std::getline(inputFile, inputLine)) {
        // 0            1           2           3           4           5
        // move, numCratesToMove, from, sourceStackNumber, to, destinationStackNumber
        auto instructionParts = splitStringByDelimiter(inputLine, ' ');
        MoveInstruction moveInstruction = {
            .numCratesToMove = std::stoi(instructionParts[1]),
            .sourceStackNumber = std::stoi(instructionParts[3]),
            .destinationStackNumber = std::stoi(instructionParts[5])
        };
        moveInstructions.push_back(moveInstruction);
    }

    return moveInstructions;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("./input.txt");
    auto crateStacks = parseCrateStacks(inputFile);
    auto moveInstructions = parseMoveInstructions(inputFile);

    // Debugging
    //    for (auto i = 0; i < crateStacks.size(); i++) {
    //        std::cout << "Stack " << i + 1 << ": ";
    //        for (auto j = 0; j < crateStacks[i].size(); j++) {
    //            std::cout << crateStacks[i][j];
    //        }
    //        std::cout << "\n";
    //    }
    // Debugging
    //    for (auto instruction : moveInstructions) {
    //        std::cout << "Instruction: move " << instruction.numCratesToMove << " from " << 
    //            instruction.sourceStackNumber << " to " << instruction.destinationStackNumber << "\n"; 
    //    }

    for (auto instruction : moveInstructions) {
        auto &sourceStack = crateStacks[instruction.sourceStackNumber - 1];
        auto &destinationStack = crateStacks[instruction.destinationStackNumber - 1];

        // std::cout << "INSTRUCTION:\n";
        for (auto i = 0; i < instruction.numCratesToMove; i++) {
            auto crateToMove = sourceStack.front();
            // std::cout << "\tMoving " << crateToMove << " from " << instruction.sourceStackNumber << " to " << instruction.destinationStackNumber << "\n";
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
