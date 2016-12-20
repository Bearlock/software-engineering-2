#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

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

	int bowlingScores[50];

	for(int i = 0; i < 50; i++) {
		bowlingScores[i] = 0;
	}

	int ballReference = 0;
	while(EOF != fscanf(input, "%d", &bowlingScores[ballReference])) {
		ballReference++;
	}

	int score = 0;
	int frameCount = 1;
	Frame* gameFrames[10];

	for(int i = 0; i < ballReference + 1; i++) {
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

	for(int i = 0; i < 10; i++) {
		std::cout << gameFrames[i]->getScore() << std::endl;
	}

	return 0;
}
