#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>


int main(int argc, char *argv[]) {

	FILE *input;
	input = stdin;

	int frameTotals[10];

	int frameCount = 0;
	int score = 0;
	while(EOF != fscanf(input, "%d", &frameTotals[frameCount])) {
		frameCount++;
	}

	for(int i = 0; i < 10; i++) {
		score += frameTotals[i];
	}

	std::cout << "Total Score: " << score << std::endl;

	return 0;
}
