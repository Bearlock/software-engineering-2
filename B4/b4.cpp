#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Frame {

public:
	virtual int getScore() = 0;
	virtual ~Frame() {}

};

class Strike: public Frame {
private:
	int ball1;
	int ball2;

public:
	Strike(int score1, int score2): ball1(score1), ball2(score2) {

	}

	int getScore() {
		return (ball1 + ball2 + 10);
	}
};

class Spare: public Frame {
private:
	int ball1;

public:
	Spare(int score1): ball1(score1)  {

	}

	int getScore() {
		return (ball1 + 10);
	}
};

class OpenFrame: public Frame {
private:
	int ball1;
	int ball2;

public:
	OpenFrame(int score1, int score2) : ball1(score1), ball2(score2) {

	}
	int getScore() {
		return (ball1 + ball2);
	}
};

class FinalFrame: public Frame {
private:
	int ball1;
	int ball2;
	int ball3;
	
public:
	FinalFrame(int score1, int score2, int score3) : ball1(score1), ball2(score2), ball3(score3) {

	}

	int getScore() {
		return (ball1 + ball2 + ball3);
	}
};

class Facilitator {
private:

public:
	Facilitator() {

	}
	bool notDoneAgent(std::vector<Frame*> *blackboard) {
		if (blackboard->size() < 10) {
			return true;
		}
		return false;
	}

	int scoreAgent(std::vector<Frame*> blackboard) {
		int score = 0;
		for (int i = 0; i < blackboard.size(); i++) {
			score += blackboard[i]->getScore();
		}
		return score;
	}

	void frameAgent(std::vector<Frame*> *blackboard, Frame* currentFrame) {
		blackboard->push_back(currentFrame);
	}

};

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
	std::vector<Frame*> blackboard;
	Facilitator fac;
	std::srand(std::time(0));
    int randomNumber = std::rand();
    int index = 0;

	while(fac.notDoneAgent(&blackboard)) {

		if(randomNumber % 4 == 0) {
			fac.notDoneAgent(&blackboard);
		}

		else if(randomNumber % 5 == 0) {
			std::cout << "Current score: " << fac.scoreAgent(blackboard) << std::endl;
		}

		else if (randomNumber % 7 == 0) {

			if (frameCount < 10) {

				if(bowlingScores[index] == 10) {
					fac.frameAgent(&blackboard, new Strike(bowlingScores[index+1], bowlingScores[index+2]));
					index++;
				}

				else if((bowlingScores[index] + bowlingScores[index+1]) == 10) {
					fac.frameAgent(&blackboard, new Spare(bowlingScores[index+2]));
					index += 2;
				}

				else {
					fac.frameAgent(&blackboard, new OpenFrame(bowlingScores[index], bowlingScores[index + 1]));
					index += 2;
				}
			}

			else {
				fac.frameAgent(&blackboard, new FinalFrame(bowlingScores[index], bowlingScores[index + 1], bowlingScores[index + 2]));
			}

			frameCount++;
		}

		randomNumber = std::rand();
	}

	std::cout << "Final Score: " << fac.scoreAgent(blackboard) << std::endl;
	inputFileStream.close();
	return 0;
}
