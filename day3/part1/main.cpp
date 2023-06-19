#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

// https://adventofcode.com/2022/day/3

/*
 * Requirement:
 * - Lowercase item types a through z have priorities 1 through 26.
 * - Uppercase item types A through Z have priorities 27 through 52.
 * 
 * In Unicode, a-z are 97-122 and A-Z are 65-90.
 */
int getItemPriority(char item) {
    int charCode = static_cast<int>(item);
    int offset = isupper(item) ? 38 : 96;
    return charCode - offset;
}

int main() {
    std::cout << getItemPriority('Z') << std::endl;
    return 0;
}
