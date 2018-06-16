#include "GlobalTime.hpp"

GlobalTime* GlobalTime::gTime = 0;

GlobalTime::GlobalTime() {
	time = glfwGetTime();
}

GlobalTime::~GlobalTime() {};

double GlobalTime::getGobalTime() {
	if (!gTime) {
		gTime = new GlobalTime();
	}
	return gTime->time;
}

