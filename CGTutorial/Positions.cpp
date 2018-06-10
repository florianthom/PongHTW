#include "Positions.hpp"

glm::vec4 Position::getCurrentOriginPosition(glm::mat4* model) {
	return (*model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

glm::vec4 Position::getLeftX(glm::mat4* model) {
	return (*model * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

glm::vec4 Position::getUpY(glm::mat4* model) {
	return (*model * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

glm::vec4 Position::getDepthZ(glm::mat4* model) {
	return (*model * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
}



glm::vec4 Position::getLeftUpperPoint(glm::mat4* model) {
	return (*model * glm::vec4(1.0f, 1.0f, -1.0f, 1.0f));
}

glm::vec4 Position::getLeftLowPoint(glm::mat4* model) {
	return (*model * glm::vec4(1.0f, -1.0f, -1.0f, 1.0f));
}

glm::vec4 Position::getLeftBehindUpperPoint(glm::mat4* model) {
	return(*model * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

glm::vec4 Position::getLeftBehindLowPoint(glm::mat4* model) {
	return (*model * glm::vec4(1.0f, -1.0f, 1.0f, 1.0f));
}

glm::vec4 Position::getRightUpperPoint(glm::mat4* model) {
	return (*model * glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f));
}

glm::vec4 Position::getRightLowPoint(glm::mat4* model) {
	return (*model * glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f));
}

glm::vec4 Position::getRightBehindUpperPoint(glm::mat4* model) {
	return (*model * glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f));
}

glm::vec4 Position::getRightBehindLowPoint(glm::mat4* model) {
	return (*model * glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f));
}