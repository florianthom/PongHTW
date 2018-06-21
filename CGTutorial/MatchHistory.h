#pragma once
#include "State.h"
#include "texture.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "text2D.h"


class MatchHistory :
	public State
{
private:
	// High-score data: score and player name.

	GLuint* programmID;
	glm::mat4 ModelAll;
	glm::mat4 * View;
	glm::mat4 * Projection;
	glm::vec3 Position;
	double groesse;
	void sendModel(glm::mat4 ModelToSend);
	GLuint TextureOrange;
	void AddNewScore(const std::string & strName, double ulScore);
	char filename[18] = "match_history.txt";
	std::vector< std::vector<std::string> > history;




public:
	MatchHistory(GLuint * programID, glm::mat4* v, glm::mat4* p, double groesse);
	~MatchHistory();
	virtual void drawSzene();
	void setMVP(glm::mat4* v, glm::mat4* p);
	void printMat4(glm::mat4 ModelToSend);
	void enterState() override;
	void exitState();
	void write_one_row(int points_player0, int points_player1);
	void lol();
	std::vector< std::vector<std::string> > read_file_and_save_in_list();
	const char * convertToStr(double * var);
	std::string append_space_at_end_of_string_to_given_max_size(std::string string, unsigned int max_size);

};

