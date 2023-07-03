#include <fstream>
#include <vector>
#include <deque>
#include "MoveInstruction.h"

std::vector<std::deque<char>> parseCrateStacks(std::ifstream& inputFile);

std::vector<MoveInstruction> parseMoveInstructions(std::ifstream& inputFile);

