#include "State.h"
#pragma once


void State::write_one_row_highscore(std::string text) {
	std::fstream appendFileToWorkWith;

	appendFileToWorkWith.open(filename_highscore, std::fstream::in | std::fstream::out | std::fstream::app);


	// If file does not exist, Create new file
	if (!appendFileToWorkWith)
	{
		std::cout << "Cannot open file, file does not exist. Creating new file..";

		appendFileToWorkWith.open(filename_highscore, std::fstream::in | std::fstream::out | std::fstream::trunc);
	}

	appendFileToWorkWith << text << "\n";
	appendFileToWorkWith.flush();
	appendFileToWorkWith.close();
}


void State::write_one_row_match_history(int points_player0, int points_player1) {
	std::fstream appendFileToWorkWith;

	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);

	int Hour = now->tm_hour;
	int Min = now->tm_min;
	int Sec = now->tm_sec;

	int year = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	int day = now->tm_mday;


	char text[256];
	sprintf(text, "%i %i %i %i %i %i %i", day, month, year, Hour, Min, points_player0, points_player1);

	appendFileToWorkWith.open(filename_history, std::fstream::in | std::fstream::out | std::fstream::app);


	// If file does not exist, Create new file
	if (!appendFileToWorkWith)
	{
		std::cout << "Cannot open file, file does not exist. Creating new file..";

		appendFileToWorkWith.open(filename_history, std::fstream::in | std::fstream::out | std::fstream::trunc);
	}

	appendFileToWorkWith << text << "\n";
	appendFileToWorkWith.flush();
	appendFileToWorkWith.close();
}


void State::doPlayerInput(glm::vec3 input, int location) {
}

void State::doPlayerInput(glm::vec3 input, int location, bool threeD){}