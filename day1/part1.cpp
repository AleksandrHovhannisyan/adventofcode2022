#include <iostream>
#include <fstream>	// for std::ifstream
#include <string>	// for std::stoi
#include <limits.h>	// for INT_MIN

int main() {
	// Open input file
	std::ifstream inputFile;
	inputFile.open("./input.txt");

	int maxCalories { INT_MIN };
	int currentCaloryCount { 0 };

	// Read the file line by line. Each line contains a calory count for an elf's food source.
	// Elves are separated by empty lines.
	std::string caloryLine { };
	while (std::getline(inputFile, caloryLine)) {
		// A blank or empty line signals that we're moving on to the next elf
		if (caloryLine.empty()) {
			if (currentCaloryCount > maxCalories) {
				maxCalories = currentCaloryCount;
			}
			currentCaloryCount = 0;
		} else {
			int numCalories = std::stoi(caloryLine);
			currentCaloryCount += numCalories;
		}
	}


	// Correct answer: 71124 
	std::cout << "Answer: " << maxCalories << std::endl;
	inputFile.close();

	return 0;
}
