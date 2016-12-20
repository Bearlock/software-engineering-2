#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Frame {

public:
	virtual std::string frameType() = 0;
	virtual int getScore() = 0;
	virtual int getBall1() = 0;
	virtual int getBall2() = 0;
	virtual void setBalls(int arg1, int arg2) = 0;
	virtual ~Frame() {}

};

class Strike: public Frame {
private:
	int additionalScore1;
	int additionalScore2;

public:
	Strike() {

	}

	int getScore() {
		return (additionalScore1 + additionalScore2 + 10);
	}

	int getBall1() {
		return 10;
	}

	int getBall2() {
		return 10;
	}

	void setBalls(int score1, int score2) {
		additionalScore1 = score1;
		additionalScore2 = score2;
	}

	std::string frameType() {
		return "Strike";
	}
};

class Spare: public Frame {
private:
	int ball1;
	int ball2;
	int additionalScore;

public:
	Spare(int score1, int score2): ball1(score1), ball2(score2) {

	}

	int getScore() {
		return (ball1 + ball2 + additionalScore);
	}

	int getBall1() {
		return ball1;
	}

	int getBall2() {
		return ball2;
	}

	void setBalls(int score1, int score2) {
		additionalScore = score1;
	}

	std::string frameType() {
		return "Spare";
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

	int getBall1() {
		return ball1;
	}

	int getBall2() {
		return ball2;
	}

	void setBalls(int arg1, int arg2) {

	}

	std::string frameType() {
		return "OpenFrame";
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

	int getBall1() {
		return ball1;
	}

	int getBall2() {
		return ball2;
	}

	void setBalls(int arg1, int arg2) {

	}

	std::string frameType() {
		return "FinalFrame";
	}
};

int main(int argc, char *argv[]) {
	std::string fileName;
	std::vector<int> bowlingScores;

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
	
	int numberOfPlayers;
	inputFileStream >> numberOfPlayers;
	std::cout << "Number of players: " << numberOfPlayers << std::endl;

	for(int i = 0; i < 100 * numberOfPlayers; i++) {
	 	bowlingScores.push_back(0);
	 }

	while(inputFileStream >> bowlingScore) {
		bowlingScores[ballReference] = std::stoi(bowlingScore);
		ballReference++;
	}

	std::cout << "Inputted all scores" << std::endl;

	int score = 0;
	int frameCount = 1;
	std::vector<Frame*> gameFrames;

	for(int i = 0; i < ballReference; i++) {
		if (frameCount <= numberOfPlayers * 9) {
			if(bowlingScores[i] == 10) {
				gameFrames.push_back(new Strike());
				frameCount++;
			}

			else if((bowlingScores[i] + bowlingScores[i+1]) == 10) {
				gameFrames.push_back(new Spare(bowlingScores[i], bowlingScores[i+1]));
				frameCount++;
				i++;
			}

			else {
				gameFrames.push_back(new OpenFrame(bowlingScores[i], bowlingScores[i + 1]));
				frameCount++;
				i++;
			}
		}

		else {
			if (bowlingScores[i] == 10 || bowlingScores[i] + bowlingScores[i + 1] == 10) {
				gameFrames.push_back(new FinalFrame(bowlingScores[i], bowlingScores[i + 1], bowlingScores[i + 2]));
				i += 2;
			}
			else {
				gameFrames.push_back(new FinalFrame(bowlingScores[i], bowlingScores[i + 1], 0));
				i++;
			}

			if (frameCount == numberOfPlayers * 10) {
				break;
			}

			frameCount++;

		}
	}

	std::cout << "Done with frame input" << std::endl;
	std::cout << "Frame count: " << frameCount << std::endl;

	std::vector<int> playerTotals;
	for (int i = 0; i < numberOfPlayers; i++) {
		playerTotals.push_back(-1);
	}

	for (int i = 0; i < frameCount; i++) {
		if (gameFrames[i]->frameType() == "Strike") {
			if (gameFrames[i + numberOfPlayers]->frameType() == "Strike") {
				gameFrames[i]->setBalls(gameFrames[i + numberOfPlayers]->getBall1(), gameFrames[i + (numberOfPlayers * 2)]->getBall1());
			}
			else {
				gameFrames[i]->setBalls(gameFrames[i + numberOfPlayers]->getBall1(), gameFrames[i + numberOfPlayers]->getBall2());
			}
		}
		else if (gameFrames[i]->frameType() == "Spare") {
			gameFrames[i]->setBalls(gameFrames[i + numberOfPlayers]->getBall1(), 0);
		}
	}

	for (int i = 0; i < frameCount; i++) {

		if (playerTotals[i % numberOfPlayers] == -1) {
			playerTotals[i % numberOfPlayers] = gameFrames[i]->getScore();
		}

		else {
			playerTotals[i % numberOfPlayers] += gameFrames[i]->getScore();
			
		}
	}

	std::cout << "Done with playerTotals" << std::endl;
	for(int i = 0; i < numberOfPlayers; i++) {
		std::cout << "Score for player " << i << ": " << playerTotals[i] << std::endl;
	}

	inputFileStream.close();
	return 0;
}
