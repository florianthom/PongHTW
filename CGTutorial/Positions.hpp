#include <glm/glm.hpp>
#pragma once
class Position {
public:
	static glm::vec4 getCurrentOriginPosition(glm::mat4* model);
	static glm::vec4 getLeftX(glm::mat4* model);
	static glm::vec4 getUpY(glm::mat4* model);
	static glm::vec4 getDepthZ(glm::mat4* model);

	static glm::vec4 getLeftUpperPoint(glm::mat4* model);
	static glm::vec4 getLeftBehindUpperPoint(glm::mat4* model);	
	static glm::vec4 getLeftLowPoint(glm::mat4* model);
	static glm::vec4 getLeftBehindLowPoint(glm::mat4* model);
	static glm::vec4 getRightUpperPoint(glm::mat4* model);
	static glm::vec4 getRightBehindUpperPoint(glm::mat4* model);
	static glm::vec4 getRightLowPoint(glm::mat4* model);
	static glm::vec4 getRightBehindLowPoint(glm::mat4* model);
};