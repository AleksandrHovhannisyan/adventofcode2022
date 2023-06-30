#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <optional>

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

std::optional<char> getDuplicatedItem(std::string rucksack) {
    // Split the string in half
    unsigned long midpoint { rucksack.length() / 2 };
    std::string leftCompartment = rucksack.substr(0, midpoint);
    std::string rightCompartment = rucksack.substr(midpoint);

    // Create sets of "items" (chars) from the left and right compartment strings
    std::set<char> leftCompartmentItems(leftCompartment.begin(), leftCompartment.end());
    std::set<char> rightCompartmentItems(rightCompartment.begin(), rightCompartment.end());

    // After creating the sets, compare them to each other to find the intersection
    for (auto item : leftCompartmentItems) {
        if (rightCompartmentItems.count(item)) {
            return item;
        }
    }

    // The problem didn't state whether a duplicate is guaranteed to exist, so use optional just in case
    return std::nullopt;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("./input.txt");

    std::string rucksack { };
    int totalPriorities { 0 };
    while (std::getline(inputFile, rucksack)) {
        std::optional<char> duplicatedItem = getDuplicatedItem(rucksack);
        if (duplicatedItem.has_value()) {
            int priority = getItemPriority(*duplicatedItem);
            std::cout << rucksack << " duplicated " << *duplicatedItem << " with priority " << priority << "\n";
            totalPriorities += priority;
        }
    }
    
    std::cout << "Answer: " << totalPriorities << std::endl;
    inputFile.close();
    return 0;
}
