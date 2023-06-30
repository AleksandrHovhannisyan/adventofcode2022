#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <optional>

// https://adventofcode.com/2022/day/3


int CHAR_CODE_LOWERCASE_A = static_cast<int>('a');
int CHAR_CODE_UPPERCASE_A = static_cast<int>('A');

/*
 * Requirement:
 * - Lowercase item types a through z have priorities 1 through 26.
 * - Uppercase item types A through Z have priorities 27 through 52.
 * 
 * In Unicode, a-z are 97-122 and A-Z are 65-90.
 */
int getItemPriority(char item, int lowercaseStartingPriority = 1, int uppercaseStartingPriority = 27) {
    int charCode = static_cast<int>(item);
    int offset = isupper(item) ? CHAR_CODE_UPPERCASE_A - uppercaseStartingPriority : CHAR_CODE_LOWERCASE_A - lowercaseStartingPriority;
    return charCode - offset;
}

std::optional<char> getSharedItemType(std::string rucksack1, std::string rucksack2, std::string rucksack3) {
    std::set<char> rucksack1Items(rucksack1.begin(), rucksack1.end());
    std::set<char> rucksack2Items(rucksack2.begin(), rucksack2.end());
    std::set<char> rucksack3Items(rucksack3.begin(), rucksack3.end());

    for (auto item : rucksack1Items) {
        if (rucksack2Items.contains(item) && rucksack3Items.contains(item)) {
            return item;
        }
    }

    // The problem didn't state whether a duplicate is guaranteed to exist, so use optional just in case
    return std::nullopt;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("./input.txt");

    int totalPriorities { 0 };
    std::string rucksack1 { "" };
    std::string rucksack2 { "" };
    std::string rucksack3 { "" };

    while (std::getline(inputFile, rucksack1) &&
           std::getline(inputFile, rucksack2) &&
           std::getline(inputFile, rucksack3)) {
        std::optional<char> sharedItem = getSharedItemType(rucksack1, rucksack2, rucksack3);
        if (sharedItem.has_value()) {
            int priority = getItemPriority(*sharedItem);
            totalPriorities += priority;
        }
    }
    
    std::cout << "Answer: " << totalPriorities << std::endl;
    inputFile.close();
    return 0;
}
