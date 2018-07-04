#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma once

class GlobalTime {
private:
	double time;
	GlobalTime();
	~GlobalTime();
	static GlobalTime* gTime;

public:
	static double getGobalTime();
};