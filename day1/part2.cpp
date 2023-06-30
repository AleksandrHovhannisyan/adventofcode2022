#include <iostream>
#include <fstream>	// for std::ifstream
#include <string>	// for std::stoi
#include <limits.h>	// for INT_MIN

int main() {
    // Open input file
    std::ifstream inputFile;
    inputFile.open("./input.txt");

    // A bit brute force, but it works
    int maxCalories1 { INT_MIN };
    int maxCalories2 { INT_MIN };
    int maxCalories3 { INT_MIN };
    int currentCaloryCount { 0 };

    // Read the file line by line. Each line contains a calory count for an elf's food source.
    // Elves are separated by empty lines.
    std::string caloryLine { };
    while (std::getline(inputFile, caloryLine)) {
        // A blank or empty line signals that we're moving on to the next elf
        if (caloryLine.empty()) {
            // Most calories
            if (currentCaloryCount > maxCalories1) {
                maxCalories1 = currentCaloryCount;
            }
            // Second most calories
            if (currentCaloryCount < maxCalories1 && currentCaloryCount > maxCalories2) {
                maxCalories2 = currentCaloryCount;
            }
            // Third most calories
            if (currentCaloryCount < maxCalories2 && currentCaloryCount > maxCalories3) {
                maxCalories3 = currentCaloryCount;
            }
            currentCaloryCount = 0;
        } else {
            int numCalories = std::stoi(caloryLine);
            currentCaloryCount += numCalories;
        }
    }

    std::cout << "Answer: " << maxCalories1 + maxCalories2 + maxCalories3 << std::endl;
    inputFile.close();

    return 0;
}
