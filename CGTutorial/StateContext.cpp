#include "StateContext.h"

StateContext::StateContext(GLuint * programID, glm::mat4* v, glm::mat4* p, double groesse)
{
	Triangle * szene1 = new Triangle(programID, v, p, 1);
	set_state(szene1);
}


StateContext::~StateContext()
{
}

void StateContext::set_state(State * new_state) {
	active_state = new_state;
	active_state->enterState();

}

State * StateContext::get_active_state() {
	return active_state;
}

void StateContext::drawSzene()
{
	//if (active_state)
		active_state->drawSzene();
}