#include "StateContext.h"

StateContext::StateContext(GLuint * programIDPara, glm::mat4* vPara, glm::mat4* pPara, double groessePara)
{
	programID = programIDPara;
	v = vPara;
	p = pPara;
	groesse = groessePara;

	Triangle * szene1 = new Triangle(programID, v, p, groesse);
	active_state = szene1;

	//Triangle * szene1 = new Triangle(programID, v, p, groesse);
	//active_state = szene1;
	//set_state(szene1);
}


StateContext::~StateContext()
{
}

// wird 2x aufgerufen
void StateContext::set_state(State * new_state) {
	
		 //active_state->~State();
	active_state->exitState();
	delete active_state;
	std::cout << "hi" << std::endl;
	new_state->enterState();
	active_state = new_state;

}

State * StateContext::get_active_state() {
	return active_state;
}

void StateContext::drawSzene()
{
	if (active_state) {
		active_state->drawSzene();
	}
}

GLuint * StateContext::get_program_id() {
	return programID;
}
glm::mat4* StateContext::get_view() {
	return v;
}
glm::mat4* StateContext::get_projection() {
	return p;
}
double StateContext::get_groesse() {
	return groesse;
}
