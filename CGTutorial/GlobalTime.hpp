#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma once

/*class MyTime {
protected:
	double time;

	MyTime();
	virtual ~MyTime();
};*/

class GlobalTime /*: public MyTime*/ {
private:
	double time;
	GlobalTime();
	~GlobalTime();
	static GlobalTime* gTime;

public:
	static double getGobalTime();
};