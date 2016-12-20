#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>

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

int main(int argc, char *argv[]) {

	FILE *input;
	input = stdin;

	std::vector<int> bowlingScores;

	for(int i = 0; i < 50; i++) {
		bowlingScores.push_back(0);
	}

	int ballReference = 0;
	while(EOF != fscanf(input, "%d", &bowlingScores[ballReference])) {
		ballReference++;
	}

	int score = 0;
	int frameCount = 1;
	int frameError = 0;
	int ballError = 0;
	int ballModifier = 0;
	Frame* gameFrames[10];
	std::vector<int> ballErrorFrames;
	std::vector<int> frameErrorFrames;
	std::vector<int> ballErrors;
	std::vector<int> frameErrors;

	for(int i = 0; i < bowlingScores.size(); i++) {
		if(bowlingScores[i] == 10 && bowlingScores[i + 1] == 10) {
			ballModifier++;
		}
		else if (bowlingScores[i] < 0) {
			if(i % 2 == 0) {
				ballErrorFrames.push_back((i/2) + 1 + ballModifier);
				ballErrors.push_back(bowlingScores[i]);
				ballModifier++;
			}
			else {
				ballErrorFrames.push_back((i/2) + 1 + ballModifier);
				ballErrors.push_back(bowlingScores[i]);
			}
			bowlingScores.erase(bowlingScores.begin() + i);
			ballError++;
			i--;
			ballReference--;
		}
		else if(bowlingScores[i] > 10) {
			if(i % 2 == 0) {
				ballErrorFrames.push_back((i/2) + 1 + ballModifier);
				ballErrors.push_back(bowlingScores[i]);
			}
			else {
				ballErrorFrames.push_back((i/2) + 1 + ballModifier);
				ballErrors.push_back(bowlingScores[i]);
			}

			bowlingScores.erase(bowlingScores.begin() + i);
			ballError++;
			i--;
			ballReference--;
		}
	}

	for(int i = 0; i < bowlingScores.size(); i++) {
		if (bowlingScores[i] == 10) {
			i--;
		}
		else if ((bowlingScores[i] + bowlingScores[i+1]) > 10) {
			if(i == 2 ){
				frameErrorFrames.push_back((i/2) + 1);
			}
			else {
				frameErrorFrames.push_back((i/2) + 2);
			}
			frameErrors.push_back(bowlingScores[i]);
			frameErrors.push_back(bowlingScores[i + 1]);
			frameError++;
			bowlingScores.erase(bowlingScores.begin() + i, bowlingScores.begin() + (i + 2));
			i-=2;
		}
		i++;
	}

	std::cout << "bframe" << std::endl;
	for (int i = 0; i < ballErrorFrames.size(); i++) {
		std::cout << ballErrorFrames[i] << std::endl;
	}
	std::cout << "berror" << std::endl;
	for (int i = 0; i < ballErrors.size(); i++)
	{
		std::cout << ballErrors[i] << std::endl;
	}

	std::cout << "fframe" << std::endl;
	for (int i = 0; i < frameErrorFrames.size(); i++) {
		std::cout << frameErrorFrames[i] << std::endl;
	}

	std::cout << "ferror" << std::endl;
	for (int i = 0; i < frameErrors.size(); i++)
	{
		std::cout << frameErrors[i] << std::endl;
	}

	for(int i = 0; i < bowlingScores.size() + 1; i++) {
		if (frameCount < 10) {
			if(bowlingScores[i] == 10) {
				gameFrames[frameCount - 1] = new Strike(bowlingScores[i+1], bowlingScores[i+2]);
				frameCount++;
			}
			else if((bowlingScores[i] + bowlingScores[i+1]) == 10) {
				gameFrames[frameCount - 1] = new Spare(bowlingScores[i+2]);
				frameCount++;
				i++;
			}
			else {
				gameFrames[frameCount - 1] = new OpenFrame(bowlingScores[i], bowlingScores[i + 1]);
				frameCount++;
				i++;
			}
		}
		else {
			gameFrames[frameCount - 1] = new FinalFrame(bowlingScores[i], bowlingScores[i + 1], bowlingScores[i + 2]);
			break;
		}
	}

	std::cout << "score" << std::endl;
	for(int i = 0; i < 10; i++) {
		std::cout << gameFrames[i]->getScore() << std::endl;
	}

	return 0;
}
