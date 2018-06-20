#include "GlobalTime.hpp"

GlobalTime* GlobalTime::gTime = 0;

GlobalTime::GlobalTime() {
	time = 1;
}

GlobalTime::~GlobalTime() {};

double GlobalTime::getGobalTime() {
	if (!gTime) {
		gTime = new GlobalTime();
	}
	return gTime->time;
}

