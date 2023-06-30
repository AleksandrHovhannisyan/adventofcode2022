#include <iostream>
#include <fstream>
#include <string>
#include <map>

// https://adventofcode.com/2022/day/2

// These values come from the problem statement, making enums a perfect way to represent them
enum Hand { Rock = 1, Paper = 2, Scissors = 3 };
enum Outcome { Loss = 0, Draw = 3, Win = 6 };

std::map<char, Hand> handAlphabet {
    { 'A', Hand::Rock },
    { 'B', Hand::Paper },
    { 'C', Hand::Scissors }
};

std::map<char, Outcome> outcomeAlphabet {
    { 'X', Outcome::Loss },
    { 'Y', Outcome::Draw },
    { 'Z', Outcome::Win }
};

// Map each hand to the hand it beats (e.g., Scissors is beaten by Rock, so Rock:Scissors)
std::map<Hand, Hand> handBeatenBy {
    { Hand::Rock, Hand::Scissors },
    { Hand::Paper, Hand::Rock },
    { Hand::Scissors, Hand::Paper }
};

// Inverse: map each hand to the hand that beats it (e.g., Paper beats Rock, so Rock:Paper)
std::map<Hand, Hand> handThatBeats {
    { Hand::Rock, Hand::Paper },
    { Hand::Paper, Hand::Scissors },
    { Hand::Scissors, Hand::Rock }
};

Hand getDesiredPlayerHand(Outcome desiredOutcome, Hand opponentHand) {
    switch (desiredOutcome) {
        case Outcome::Draw:
            return opponentHand;
        case Outcome::Loss:
            return handBeatenBy[opponentHand];
        case Outcome::Win:
        default:
            return handThatBeats[opponentHand];
    }
}

int main() {
    int playerScore { 0 };

    std::ifstream inputFile;
    inputFile.open("./input.txt");

    std::string rockPaperScissorsRound;
    while (std::getline(inputFile, rockPaperScissorsRound)) {
        Hand opponentHand = handAlphabet[rockPaperScissorsRound[0]];
        Outcome desiredOutcome = outcomeAlphabet[rockPaperScissorsRound[2]];
        Hand desiredPlayerHand = getDesiredPlayerHand(desiredOutcome, opponentHand);
        playerScore += desiredPlayerHand + desiredOutcome;
    }

    std::cout << "Score: " << playerScore << std::endl;
    inputFile.close();
    return 0;
}

