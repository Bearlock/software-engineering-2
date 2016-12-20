#include <string>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
	std::string fileName;
	int bowlingScores[50];

	for(int i = 0; i < 50; i++) {
		bowlingScores[i] = 0;
	}

	if (argc == 2) {
		fileName = argv[1];
	}
	else {
		std::cout << "Welcome to a bowling program. Please enter a file name: ";
		std::getline(std::cin, fileName);
	}

	int ballReference = 0;
	std::string bowlingScore;
	std::ifstream inputFileStream(fileName);

	while(inputFileStream >> bowlingScore) {
		bowlingScores[ballReference] = std::stoi(bowlingScore);
		ballReference++;
	}

	int score = 0;
	int frameCount = 1;

	for(int i = 0; i < ballReference + 1; i++) {
		if (frameCount < 10) {
			if(bowlingScores[i] == 10) {
				score +=  10 + (bowlingScores[i+1] + bowlingScores[i+2]);
				frameCount++;
			}
			else if((bowlingScores[i] + bowlingScores[i+1]) == 10) {
				score += 10 + bowlingScores[i+2];
				frameCount++;
				i++;
			}
			else {
				score += bowlingScores[i] + bowlingScores[i + 1];
				frameCount++;
				i++;
			}
		}
		else {
			score += (bowlingScores[i] + bowlingScores[i+1] + bowlingScores[i+2]);
			break;
		}
	}

	std::cout << "Final Score: " << score << std::endl;
	inputFileStream.close();
	return 0;
}
