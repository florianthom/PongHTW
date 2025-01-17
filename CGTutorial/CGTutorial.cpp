// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//using namespace glm;
// Achtung, die OpenGL-Tutorials nutzen glfw 2.7, glfw kommt mit einem ver�nderten API schon in der Version 3 
// Befindet sich bei den OpenGL-Tutorials unter "common"
#include "shader.hpp"
// Wuerfel und Kugel
#include "objects.hpp"
// Ab Uebung5 werden objloader.hpp und cpp benoetigt
#include "objloader.hpp"
// Ab Uebung7 werden texture.hpp und cpp benoetigt
#include "texture.hpp"
// glm-Bibliothek f�r Matrix-Operationen (fehlen in Version3), glew-Bibliothek, um API-Funktionen > 1.1 nutzen zu k�nnen
// glfw-Bibliothek, um OpenGL plattformunabh�ngig nutzen zu k�nnen (z. B. Fenster �ffnen)


#include "Obj3D.h"
#include "time.h"
#include "iostream"
#include "Ball.hpp"
#include "Szene1.h"
#include "Szene2.h"
#include "Szene3.h"
#include "Triangle.h"
#include "text2D.h"
#include "StateContext.h"
#include <thread>
#include "Highscore.h"
#include "MatchHistory.h"


//Header: hier steht alles was man in cpp findet -> Funktionen
//Cpp-File: hier steht der Gro�teil der Implementierung
StateContext * state_context;
Szene1 * szene1;
Szene2 * szene2;
Szene3 * szene3;
Triangle * triangle1;
Highscore * highscore;

//0 = False; 1 = True

float angle_x = 0.0f;
//float * angle_y;
float angle_y = 0.0f;
float angle_z = 0.0f;
bool r_pressed = false;
bool e_pressed = false;

bool w_pressed = false;
bool a_pressed = false;
bool s_pressed = false;
bool d_pressed = false;

bool i_pressed = false;
bool j_pressed = false;
bool k_pressed = false;
bool l_pressed = false;



bool up_pressed = false;
bool down_pressed = false;
bool left_pressed = false;
bool right_pressed = false;


// Funktion, die angibt, was man im Fehlerfall machen m�chte
// Funktion wird glfwSetErrorCallback �bergeben, da glfw die Fehlerbehandlung f�r uns ausf�hrt
void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

// Funktion, die angibt, was man im Fall einer Tastatureingabe machen m�chte
// Funktion wird glfwKeyCallBack �bergeben, da glfw die Eingaben verwaltet, bzw auch gleich einem window zuordnet



void get_up() {
	while (w_pressed) {
		//std::cout << "" << std::endl;
		state_context->get_active_state()->doPlayerInput(glm::vec3(0.0f, 0.000004f, 0.0f), 0);
	}

}

void get_up3D() {
	while (up_pressed) {
		//std::cout << "" << std::endl;
		state_context->get_active_state()->doPlayerInput(glm::vec3(0.0f, 0.000003f, 0.0f), 0, true);
	}

}

void go_left() {
	while (a_pressed) {
		//std::cout << "" << std::endl;
		state_context->get_active_state()->doPlayerInput(glm::vec3(0.000004f, 0.0f, 0.0f), 1);
	}
}

void go_left3D() {
	while (left_pressed) {
		//std::cout << "" << std::endl;
		state_context->get_active_state()->doPlayerInput(glm::vec3(0.000003f, 0.0f, 0.0f), 0, true);
	}
}

void go_right() {
	while (d_pressed) {
		//std::cout << "" << std::endl;
		state_context->get_active_state()->doPlayerInput(glm::vec3(-0.000004f, 0.0f, 0.0f), 1);
	}
}

void go_right3D() {
	while (right_pressed) {
		//std::cout << "" << std::endl;
		state_context->get_active_state()->doPlayerInput(glm::vec3(-0.000003f, 0.0f, 0.0f), 0, true);
	}
}


void get_down() {
	while (s_pressed) {
		//std::cout << "" << std::endl;
		state_context->get_active_state()->doPlayerInput(glm::vec3(0.0f, -0.000004f, 0.0f), 0);
	}
}

void get_down3D() {
	while (down_pressed) {
		//std::cout << "" << std::endl;
		state_context->get_active_state()->doPlayerInput(glm::vec3(0.0f, -0.000003f, 0.0f), 0, true);
	}
}

void get_up_p2() {
	while (i_pressed) {
		//std::cout << "" << std::endl;
		state_context->get_active_state()->doPlayerInput(glm::vec3(0.0f, 0.000004f, 0.0f), 2);
	}
}

void go_left2() {
	while (j_pressed) {
		//std::cout << "" << std::endl;
		state_context->get_active_state()->doPlayerInput(glm::vec3(0.000004f, 0.0f, 0.0f), 3);
	}
}

void go_right2() {
	while (l_pressed) {
		//std::cout << "" << std::endl;
		state_context->get_active_state()->doPlayerInput(glm::vec3(-0.000004f, 0.0f, 0.0f), 3);
	}
}

void get_down_p2() {
	while (k_pressed) {
		//std::cout << "" << std::endl;
		state_context->get_active_state()->doPlayerInput(glm::vec3(0.0f, -0.000004f, 0.0f), 2);
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
		state_context->set_state(new Triangle(state_context->get_program_id(), state_context->get_view(), state_context->get_projection(), state_context->get_groesse()));

	}
	else if (key == GLFW_KEY_2 && action == GLFW_RELEASE) {
		state_context->set_state(new Szene1(state_context->get_program_id(), state_context->get_view(), state_context->get_projection(), state_context->get_groesse(),1));

	}
	else if (key == GLFW_KEY_3 && action == GLFW_RELEASE) {
		state_context->set_state(new Szene1(state_context->get_program_id(), state_context->get_view(), state_context->get_projection(), state_context->get_groesse(),2));

	}
	else if (key == GLFW_KEY_4 && action == GLFW_RELEASE) {
		state_context->set_state(new Szene2(state_context->get_program_id(), state_context->get_view(), state_context->get_projection(), state_context->get_groesse(),1));

	}
	else if (key == GLFW_KEY_5 && action == GLFW_RELEASE) {
		state_context->set_state(new Szene2(state_context->get_program_id(), state_context->get_view(), state_context->get_projection(), state_context->get_groesse(), 2));

	}
	else if (key == GLFW_KEY_6 && action == GLFW_RELEASE) {
		state_context->set_state(new Szene2(state_context->get_program_id(), state_context->get_view(), state_context->get_projection(), state_context->get_groesse(), 4));

	}
	else if (key == GLFW_KEY_7 && action == GLFW_RELEASE) {
		state_context->set_state(new Szene3(state_context->get_program_id(), state_context->get_view(), state_context->get_projection(), state_context->get_groesse()));

	}
	else if(key == GLFW_KEY_8 && action == GLFW_RELEASE){
		state_context->set_state(new Highscore(state_context->get_program_id(), state_context->get_view(), state_context->get_projection(), state_context->get_groesse()));

	}
	else if (key == GLFW_KEY_9 && action == GLFW_RELEASE) {
		state_context->set_state(new MatchHistory(state_context->get_program_id(), state_context->get_view(), state_context->get_projection(), state_context->get_groesse()));

	}

	///////////////////////////////////// PADDLE CONTROL///////////////////////////////////////////

	// Player 1 Paddles
	else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		w_pressed = true;
		std::thread t1(get_up);
		t1.detach();
	}

	else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		w_pressed = false;
	}

	else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
			a_pressed = true;
			std::thread t1(go_left); 
			t1.detach();
	}
	else if (key == GLFW_KEY_C && (action == GLFW_PRESS || action == GLFW_REPEAT || action == GLFW_RELEASE)) {
		angle_y = angle_y + 5.0f;

	}
	else if (key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT || action == GLFW_RELEASE)) {
		angle_x = angle_x + 5.0f;

	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		a_pressed = false;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
			s_pressed = true;
			std::thread t1(get_down); 
			t1.detach();
	}
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		up_pressed = true;
		std::thread t1(get_up3D);
		t1.detach();
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		down_pressed = true;
		std::thread t1(get_down3D); 
		t1.detach();
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		right_pressed = true;
		std::thread t1(go_right3D);
		t1.detach();
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
	left_pressed = true;
		std::thread t1(go_left3D);
		t1.detach();
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		left_pressed = false;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
		right_pressed = false;
	}
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
		up_pressed = false;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
		down_pressed = false;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		s_pressed = false;
	}

	else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		d_pressed = true;
		std::thread t1(go_right);
		t1.detach();
	}

	else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		d_pressed = false;
	}

	// Player 2 Paddles
	else if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		i_pressed = true;
		std::thread t1(get_up_p2);
		t1.detach();
	}

	else if (key == GLFW_KEY_I && action == GLFW_RELEASE) {
		i_pressed = false;
	}

	else if (key == GLFW_KEY_J && action == GLFW_PRESS) {
		j_pressed = true;
		std::thread t1(go_left2);
		t1.detach();
	}

	else if (key == GLFW_KEY_J && action == GLFW_RELEASE) {
		j_pressed = false;
	}

	else if (key == GLFW_KEY_K && action == GLFW_PRESS) {
		k_pressed = true;
		std::thread t1(get_down_p2);
		t1.detach();
	}

	else if (key == GLFW_KEY_K && action == GLFW_RELEASE) {
		k_pressed = false;
	}

	else if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		l_pressed = true;
		std::thread t1(go_right2);
		t1.detach();
	}

	else if (key == GLFW_KEY_L && action == GLFW_RELEASE) {
		l_pressed = false;
	}


	else if (key == GLFW_KEY_ESCAPE &&  action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

// Diese Drei Matrizen global (Singleton-Muster), damit sie jederzeit modifiziert und
// an die Grafikkarte geschickt werden koennen
//alle drei ZUSAMMEN MULTIPLIZIERT ergeben den (einen) Punkt oder die Punkte Matrix
glm::mat4 Projection;
// wo ist Betrachter aka Kamera, Wo schaut er hin, wo ist oben (eig 3x3 matrix)
glm::mat4 View;
// alle Opertionen (rotation,translation,skalierung) werden hier als Einheit in dieser Matrix gepspeichert -> nichts passier d.h. Model = Einheitsmatrix = kein Einfluss
glm::mat4 Model;
GLuint programID;

void sendMVP()
{
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model;
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform, konstant fuer alle Eckpunkte
	glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "M"), 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "V"), 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "P"), 1, GL_FALSE, &Projection[0][0]);
}

void drawCS() {
	glm::mat4 Save = Model;
	Model = glm::scale(Model, glm::vec3(10 * 1.0 / 1.0, 1.0 / 100.0, 1.0 / 100.0));
	sendMVP();
	drawCube();

	Model = Save;
	Model = glm::scale(Model, glm::vec3(1.0 / 100.0, 10 * 1.0 / 1.0, 1.0 / 100.0));
	sendMVP();
	drawCube();

	Model = Save;
	Model = glm::scale(Model, glm::vec3(1.0 / 100.0, 1.0 / 100.0, 10 * 1.0 / 1.0));
	sendMVP();
	drawCube();


	Model = Save;
}

double counter_richtung = 0;
int flag = true;
int moove = 0;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	if (width < 300)
		width = 300;
	if (height < 300)
		height = 300;
	glViewport(0, 0, width, height);
}



void window_size_callback(GLFWwindow* window, int widthPara, int heightPara)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetWindowSize(window, widthPara, heightPara);
}

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	// Fehler werden auf stderr ausgegeben, s. o.
	glfwSetErrorCallback(error_callback);



	// -> man brauch mindestens 1 Fenster(window) f�r OpenGL (wo muss grafischer Output hin...)
	// Somit wird hier 1 window und dem damit verbundenen Context erzeugt
	// ---------------> As the window and context are inseparably linked, the object pointer is used as both a context and window handle
	// glfwWindowHint vorher aufrufen, um erforderliche Resourcen festzulegen
	GLFWwindow* window = glfwCreateWindow(1024, // Breite
		768,  // Hoehe
		"Pong HTW", // Ueberschrift
		NULL,  // use windowed mode
		NULL); // shared windoe

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Setzt das Fenster/Context als Output
	// was ist context: Ein Kontext speichert den gesamten Status, der dieser Instanz von OpenGL zugeordnet ist
	//		Stellen Sie sich einen Kontext als ein Objekt vor, das (alle) Elemente von OpenGL enth�lt (man kann mehrere Contexts haben)
	//		Damit OpenGL-Befehle funktionieren, muss ein Kontext aktuell sein. Alle OpenGL-Befehle beeinflussen den Status des aktuellen Kontextes
	//		denken an Java, wo man auch in einen bestimmten Context zeichnen konnte
	// Make the window's context current (wird nicht automatisch gemacht)
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	// GLEW erm�glicht Zugriff auf OpenGL-API > 1.1
	glewExperimental = true; // Needed for core profile

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Funktion +berwacht Keyboard und f�r die Funktion key_callback aus, falls eine Taste gedr�ckt wird
	glfwSetKeyCallback(window, key_callback);

	// setzten einer L�schfarbe (context-unabh�ngig), ABER NICHT ANWENDUNG EINES L�SCHVORGANGES
	// Dark blue background
	// Parameter: R G B Deckkraft
	// Werte der Parameter gehen nicht von 0-255 sondern von 0-1
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	glfwSetWindowPos(window, 400, 200);

	// Create and compile our GLSL program from the shaders

	programID = LoadShaders("StandardShading.vertexshader", "StandardTransparentShading.fragmentshader");


	// Shader auch benutzen !
	/**--1*/glUseProgram(programID);

	// sagt, dass die z Werte angezeigt werden, die kleienr sind (das nicht beide angezeigt werden, da wir ja nur die "Oberseite" sehen wollen)
	/**--1*/glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Load the texture
	//benoetigt 24 bit bmp picture
	GLuint TextureMandrill = loadBMP_custom("mandrill.bmp");
	GLuint TextureStone = loadBMP_custom("Steinwand.bmp");
	GLuint TextureRed = loadBMP_custom("red.bmp");
	GLuint TextureYellow = loadBMP_custom("yellow.bmp");
	GLuint TextureGreen = loadBMP_custom("green.bmp");
	GLuint TextureBlack = loadBMP_custom("black.bmp");
	GLuint TextureStripes = loadBMP_custom("streifen-maritim-1_1.bmp");
	GLuint TextureOrange = loadBMP_custom("orange.bmp");


	// Bind our texture in Texture Unit 0

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureStone);

	// Set our "myTextureSampler" sampler to user Texture Unit 0
	/**--*/glUniform1i(glGetUniformLocation(programID, "myTextureSampler"), 0);
	//-----------------------------------------------

	time_t t_start = time(0);/*time(0)*/;
	time_t t_check;
	time_t needed;
	int frame_counter = 0;


	const double maxFPS = 30.0;

	const double maxPeriod = 1.0 / maxFPS;
	double lastTime = 0.0;


	szene3 = new Szene3(&programID, &View, &Projection, 1);
	triangle1 = new Triangle(&programID, &View, &Projection, 1);
	state_context = new StateContext(&programID, &View, &Projection, 1);




	// Vector-Variable ist nur zum testen/ausgeben der Position eines Balls auf der Konsole
	glm::vec3 tempPos;


	while (!glfwWindowShouldClose(window))
	{
		double timeLimiter = glfwGetTime();
		double deltaTime = timeLimiter - lastTime;

		if (deltaTime >= maxPeriod) {
			lastTime = timeLimiter;

			frame_counter += 1;
			t_check = time(0);
			needed = difftime(t_check, t_start);
			// * 100 damit wir time in milli sekunden bekommen, dadurch m�ssen wir aber auch frames *1000 rechnen, da Ursprungsgleichung: Gesamtframes / Gesamtzeit in Seconds
			/*if ((1000 * needed) != 0)
				std::cout << "current fps: " << ((frame_counter * 1000) / (1000 * needed)) << std::endl;*/

			// 1. L�schen des voherigen Bildes
			// Clear the screen und l�sche z speicher
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// 2. JETZT Erstellen des neuen Bildes (aka Rendern des neuen Bildes mit MVP-Prinzip (Model, View, Projection))

			// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units d.h. zwischen der Range von 0.1 bis 100 wird alles angezeigt
			// Parameter: 1.: wie weit ist W�rfel hinten, 2. Seitenverh�ltnis, 3.  + 4. kA
			Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

			// Wo steht Kamera
			// Camera matrix
			View = glm::lookAt(glm::vec3(0, 0, -5), // Wo ist Kamera / Betrachter
				glm::vec3(0, 0, 0),  // Wo schaut er hin
				glm::vec3(0, 1, 0)); // Wo ist oben (damit man sicherstellt, dass Betrachter nicht schief guckt)

		// was passiert mit Objekten bezogen auf Welt
		// Model matrix : an identity matrix = Einheitsmatrix = Es passiert nichts = kein Einfluss ( ??= Am Ursprung?? -> war voheriger Kommentar)
			Model = glm::mat4(1.0f);

			//Model = glm::rotate(altes Model,Winkel, Vektor der die Achse aufspannt um den sich gedreht werden soll-> x=Daumen,y=Zeigefinger,z=Mittelfinger)
			/*Model = glm::rotate(Model, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
			Model = glm::rotate(Model, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
			Model = glm::rotate(Model, angle_z, glm::vec3(0.0f, 0.0f, 1.0f));*/

			
			Model = glm::scale(Model, glm::vec3(0.4f, 0.4f, 0.4f));
			sendMVP();
			glBindTexture(GL_TEXTURE_2D, TextureStripes);
			//drawCS();
			//drawCube();

			state_context->drawSzene();

			glm::vec4 lightPos = glm::vec4(-3, 3, -2, 1);
			glUniform3f(glGetUniformLocation(programID, "LightPosition_worldspace"), lightPos.x, lightPos.y, lightPos.z); // Variable "LightPosition_worldspace" ist in Fragment-Shader definiert und damit in Grafik-Speicher vorhanden

			// Swap buffers
			glfwSwapBuffers(window);
			// gettet alle Events und ruft eventuell Callback auf falls individuell vorhanden
			glfwPollEvents();
		}
	}
	glDeleteProgram(programID);
	// Cleanup VBO and shader
	glDeleteTextures(1, &TextureMandrill);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

