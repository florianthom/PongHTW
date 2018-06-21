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
	std::cout << "\n";
}







// goal: write: date player0-score
//				player0-score
//				player1-score
//		repeat...
// so: 3 rows are needed for 1 total information
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
	//printf(text);

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
	std::cout << "\n";

}
// why ista return of player1 ? Your MUST have at least 1 player
Paddle* State::get_paddle_player1() {
	return player1;
}

// if player_number != 2 aka you have only 1 player -> this function will return NULL
Paddle* State::get_paddle_player2() {
	if (player_number > 1)
		return player2;
	else
		return NULL;
}

Paddle* State::get_paddle_player3() {
	if (player_number > 2)
		return player3;
	else
		return NULL;
}

Paddle* State::get_paddle_player4() {
	if (player_number > 3)
		return player4;
	else
		return NULL;
}