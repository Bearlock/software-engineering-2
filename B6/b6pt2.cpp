#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>

int main(int argc, char *argv[]) {

	std::vector<int> frameTotals;
	std::vector<char> flags;
	std::vector<int> ballErrorFrames;
	std::vector<int> ballErrors;
	std::vector<int> frameErrorFrames;
	std::vector<int> frameErrors;

	int frameCount = 0;
	int score = 0;
	std::string flag;
	int framesandscores;

	while(std::cin.good()) {
		if (std::getline(std::cin, flag)) {
			if(flag == "bframe") {
				while(std::cin >> framesandscores) {
					ballErrorFrames.push_back(framesandscores);
				}
				std::cin.clear();
			}
			else if(flag == "berror") {
				while(std::cin >> framesandscores) {
					ballErrors.push_back(framesandscores);
				}
				std::cin.clear();
			}
			else if(flag == "fframe") {
				while(std::cin >> framesandscores) {
					frameErrorFrames.push_back(framesandscores);
				}
				std::cin.clear();
			}
			else if(flag == "ferror") {
				while(std::cin >> framesandscores) {
					frameErrors.push_back(framesandscores);
				}
				std::cin.clear();
			}
			else if(flag == "score") {
				while(std::cin >> framesandscores) {
					frameTotals.push_back(framesandscores);
				}
				std::cin.clear();
			}
		}
	}

	for(int i = 0; i < frameTotals.size(); i++) {
		score += frameTotals[i];
	}

	for(int i = 0; i < ballErrorFrames.size(); i++) {
		std::cout << "Ball error on frame " << ballErrorFrames[i] << ": " << ballErrors[i] << " is an invalid roll" << std::endl;
	}

	int j = 0;
	for(int i = 0; i < frameErrorFrames.size(); i++) {
		std::cout << "Frame error on frame " << frameErrorFrames[i] << ": " << frameErrors[j] << ", " << frameErrors[j + 1] << " is an invalid frame" << std::endl;
		j += 2;
	}

	std::cout << "Total Score: " << score << std::endl;
	std::cout << "Total Errors: " << frameErrorFrames.size() + ballErrorFrames.size() << std::endl;
	return 0;
}
