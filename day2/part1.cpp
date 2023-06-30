#include <iostream>
#include <fstream>
#include <string>
#include <map>

// https://adventofcode.com/2022/day/2

// These values come from the problem statement, making enums a perfect way to represent them
enum Hand { Rock = 1, Paper = 2, Scissors = 3 };
enum Outcome { Loss = 0, Draw = 3, Win = 6 };

// Map each hand to the hand it beats. Example: Rock beats Scissors.
std::map<Hand, Hand> handBeatenBy {
    { Hand::Rock, Hand::Scissors },
    { Hand::Paper, Hand::Rock },
    { Hand::Scissors, Hand::Paper }
};

// The problem uses A,B,C for the opponent's hands and X,Y,Z for the player's hands
Hand getHand(char hand) {
    switch (hand) {
        case 'A':
        case 'X':
            return Hand::Rock;
        case 'B':
        case 'Y':
            return Hand::Paper;
        case 'C':
        case 'Z':
        default:
            return Hand::Scissors;
    }
}

Outcome getOutcome(Hand opponentHand, Hand playerHand) {
    if (opponentHand == playerHand) {
        return Outcome::Draw;
    }
    if (handBeatenBy[playerHand] == opponentHand) {
        return Outcome::Win;
    }
    return Outcome::Loss;
}

int main() {
    int playerScore { 0 };

    std::ifstream inputFile;
    inputFile.open("./input.txt");
    
    std::string rockPaperScissorsRound;
    while (std::getline(inputFile, rockPaperScissorsRound)) {
        Hand opponentHand = getHand(rockPaperScissorsRound[0]);
        Hand playerHand = getHand(rockPaperScissorsRound[2]);
        Outcome outcome = getOutcome(opponentHand, playerHand); 
        playerScore += playerHand + outcome;
    }

    std::cout << "Score: " << playerScore << std::endl;
    inputFile.close();
    return 0;
}
