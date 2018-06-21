#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Ball.hpp"
#include "Collision.hpp"
#include "iostream"
#include "texture.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "text2D.h"
#include <iostream>
#include <algorithm>
#include <ctime>
//#include "StateContext.h"
#pragma once

class State
{
public:

	char filename_highscore[15] = "highscores.txt";
	char filename_history[18] = "match_history.txt";

	virtual void drawSzene() = 0;
	virtual void enterState() = 0;
	virtual void exitState() = 0;
	virtual void lol() = 0;
	void write_one_row_highscore(std::string text);
	void write_one_row_match_history(int points_player0, int points_player1);

};

