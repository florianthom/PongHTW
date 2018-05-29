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
// Achtung, die OpenGL-Tutorials nutzen glfw 2.7, glfw kommt mit einem veränderten API schon in der Version 3 
// Befindet sich bei den OpenGL-Tutorials unter "common"
#include "shader.hpp"
// Wuerfel und Kugel
#include "objects.hpp"
// Ab Uebung5 werden objloader.hpp und cpp benoetigt
#include "objloader.hpp"
// Ab Uebung7 werden texture.hpp und cpp benoetigt
#include "texture.hpp"
// glm-Bibliothek für Matrix-Operationen (fehlen in Version3), glew-Bibliothek, um API-Funktionen > 1.1 nutzen zu können
// glfw-Bibliothek, um OpenGL plattformunabhängig nutzen zu können (z. B. Fenster öffnen)


#include "Obj3D.h"
#include "time.h"
#include "iostream"
#include "Szene1.h"
#include "Szene2.h"


//Header: hier steht alles was man in cpp findet -> Funktionen
//Cpp-File: hier steht der Großteil der Implementierung

//0 = False; 1 = True

float angle_x = 0.0f;
float angle_y = 0.0f;
float angle_z = 0.0f;

// Funktion, die angibt, was man im Fehlerfall machen möchte
// Funktion wird glfwSetErrorCallback übergeben, da glfw die Fehlerbehandlung für uns ausführt
void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

// Funktion, die angibt, was man im Fall einer Tastatureingabe machen möchte
// Funktion wird glfwKeyCallBack übergeben, da glfw die Eingaben verwaltet, bzw auch gleich einem window zuordnet
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	case GLFW_KEY_R:
		angle_y = angle_y + 5.0f;
		break;
	case GLFW_KEY_Q:
		angle_y -= 5.0;
		break;

	case GLFW_KEY_E:
		angle_x += 5.0;
		break;
	case GLFW_KEY_W:
		angle_z += 5.0;
		break;
	default:
		break;
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

void moove_balken() {
	if(counter_richtung < 3 && flag){
	Model = glm::translate(Model, glm::vec3(counter_richtung, 0.0, 0.0));
	counter_richtung = counter_richtung + 0.01;
	std::cout << "if" << std::endl;
	}
	else {
		flag = false;
		Model = glm::translate(Model, glm::vec3(counter_richtung, 0.0, 0.0));
		counter_richtung = counter_richtung-0.01;
		std::cout << "else" << std::endl;
		if (counter_richtung < -3) {
			flag = true;

		}

	}

}

void drawBalken() {
	glm::mat4 Save = Model;
	Model = glm::scale(Model, glm::vec3(1.0, 1.0 / 5.0, 1.0 / 5.0));
	Model = glm::translate(Model, glm::vec3(0, 5.0, 0.0));
	moove_balken();
	sendMVP();
	drawCube();
	Model = Save;

}


// problem: unterschiedliche Ergebnisse, wenn man auf unterschiedlichen achsen scaled
// Lösung ggf erst skalieren, alles komplett abhängig machen von groesse und dann 2 davon rotieren (damit Verhältnisse gleich bleiben)
//void drawSzene1(double groesse) {
//	glm::mat4 Save = Model;
//	Model = glm::scale(Model, glm::vec3(4* groesse, 1.0 / 20.0, 1.0 / 20.0));
//	glm::mat4 SaveScale = Model;
//	Model = glm::translate(Model, glm::vec3(0, 30.0 * groesse, 0.0));
//	sendMVP();
//	drawCube();
//	Model = SaveScale;
//	Model = glm::translate(Model, glm::vec3(0, -30.0 * groesse, 0.0));
//	sendMVP();
//	drawCube();
//	Model = Save;
//
//	// mitte = wie viel , vec3=Achse um die gedreht werden soll
//	Model = glm::scale(Model, glm::vec3(1.0/20.0, 1.5 * groesse, 1.0 / 20.0));
//	Model = glm::translate(Model, glm::vec3(79.0 * groesse, 0.0, 0.0));
//	sendMVP();
//	drawCube();
//	Model = Save;
//
//	Model = glm::scale(Model, glm::vec3(1.0 / 20.0, 1.5 * groesse, 1.0 / 20.0));
//	Model = glm::translate(Model, glm::vec3(-79* groesse, 0.0, 0.0));
//	sendMVP();
//	drawCube();
//	Model = Save;
//
//}


/*void drawSzene2(double groesse) {
	// top and buttom
	glm::mat4 Save = Model;
	Model = glm::scale(Model, glm::vec3(2 * groesse, 1.0 / 20.0, 1.0 / 20.0));
	glm::mat4 SaveScale = Model;
	Model = glm::translate(Model, glm::vec3(0, 80.0 * groesse, 0.0));
	sendMVP();
	drawCube();
	Model = SaveScale;
	Model = glm::translate(Model, glm::vec3(0, -80.0 * groesse, 0.0));
	sendMVP();
	drawCube();
	Model = Save;

	// left and right
	Model = glm::rotate(Model, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	Model = glm::scale(Model, glm::vec3(2 * groesse, 1.0 / 20.0, 1.0 / 20.0));
	glm::mat4 SaveRotation = Model;
	Model = glm::translate(Model, glm::vec3(0.0, 80 * groesse, 0.0));
	sendMVP();
	drawCube();
	Model = SaveRotation;
	Model = glm::translate(Model, glm::vec3(0.0, -80 * groesse, 0.0));
	sendMVP();
	drawCube();
	Model = Save;

	//little verticals
	Model = glm::rotate(Model, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	Model = glm::scale(Model, glm::vec3(1.05 * groesse, 1.0 / 20.0, 1.0 / 20.0));
	glm::mat4 SaveLT = Model;
	Model = glm::translate(Model, glm::vec3(0.0, 39 * groesse, 0.0));
	Model = glm::translate(Model, glm::vec3(2.81 * groesse, 0.0, 0.0));
	sendMVP();
	drawCube();
	Model = SaveLT;
	Model = glm::translate(Model, glm::vec3(0.0, -39 * groesse, 0.0));
	Model = glm::translate(Model, glm::vec3(2.81 * groesse, 0.0, 0.0));
	sendMVP();
	drawCube();
	Model = SaveLT;
	Model = glm::translate(Model, glm::vec3(0.0, 39 * groesse, 0.0));
	Model = glm::translate(Model, glm::vec3(-2.81 * groesse, 0.0, 0.0));
	sendMVP();
	drawCube();
	Model = SaveLT;
	Model = glm::translate(Model, glm::vec3(0.0, -39 * groesse, 0.0));
	Model = glm::translate(Model, glm::vec3(-2.81 * groesse, 0.0, 0.0));
	sendMVP();
	drawCube();


	Model = Save;

	//little horizontals
	Model = glm::scale(Model, glm::vec3(1.05f * groesse, 1.0 / 20.0, 1.0 / 20.0));
	glm::mat4 SaveL = Model;
	Model = glm::translate(Model, glm::vec3(0.0, 39 * groesse, 0.0));
	Model = glm::translate(Model, glm::vec3(2.81 * groesse, 0.0, 0.0));
	sendMVP();
	drawCube();
	Model = SaveL;
	Model = glm::translate(Model, glm::vec3(0.0, -39 * groesse, 0.0));
	Model = glm::translate(Model, glm::vec3(2.81 * groesse, 0.0, 0.0));
	sendMVP();
	drawCube();
	Model = SaveL;
	Model = glm::translate(Model, glm::vec3(0.0, 39 * groesse, 0.0));
	Model = glm::translate(Model, glm::vec3(-2.81 * groesse, 0.0, 0.0));
	sendMVP();
	drawCube();
	Model = SaveL;
	Model = glm::translate(Model, glm::vec3(0.0, -39 * groesse, 0.0));
	Model = glm::translate(Model, glm::vec3(-2.81 * groesse, 0.0, 0.0));
	sendMVP();
	drawCube();


	Model = Save;


}
*/

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

	// -> man brauch mindestens 1 Fenster(window) für OpenGL (wo muss grafischer Output hin...)
	// Somit wird hier 1 window und dem damit verbundenen Context erzeugt
	// ---------------> As the window and context are inseparably linked, the object pointer is used as both a context and window handle
	// glfwWindowHint vorher aufrufen, um erforderliche Resourcen festzulegen
	GLFWwindow* window = glfwCreateWindow(1024, // Breite
										  768,  // Hoehe
										  "CG - Tutorial", // Ueberschrift
										  NULL,  // windowed mode
										  NULL); // shared windoe

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Setzt das Fenster/Context als Output
	// was ist context: Ein Kontext speichert den gesamten Status, der dieser Instanz von OpenGL zugeordnet ist
	//		Stellen Sie sich einen Kontext als ein Objekt vor, das (alle) Elemente von OpenGL enthält (man kann mehrere Contexts haben)
	//		Damit OpenGL-Befehle funktionieren, muss ein Kontext aktuell sein. Alle OpenGL-Befehle beeinflussen den Status des aktuellen Kontextes
	//		denken an Java, wo man auch in einen bestimmten Context zeichnen konnte
	// Make the window's context current (wird nicht automatisch gemacht)
    glfwMakeContextCurrent(window);

	// Initialize GLEW
	// GLEW ermöglicht Zugriff auf OpenGL-API > 1.1
	glewExperimental = true; // Needed for core profile

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Funktion +berwacht Keyboard und für die Funktion key_callback aus, falls eine Taste gedrückt wird
	glfwSetKeyCallback(window, key_callback);

	// setzten einer Löschfarbe (context-unabhängig), ABER NICHT ANWENDUNG EINES LÖSCHVORGANGES
	// Dark blue background
	// Parameter: R G B Deckkraft
	// Werte der Parameter gehen nicht von 0-255 sondern von 0-1
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Create and compile our GLSL program from the shaders
	// programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");

	programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");


	// Shader auch benutzen !
	glUseProgram(programID);

	// sagt, dass die z Werte angezeigt werden, die kleienr sind (das nicht beide angezeigt werden, da wir ja nur die "Oberseite" sehen wollen)
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Load the texture
	//benoetigt 24 bit bmp picture
	GLuint Texture = loadBMP_custom("mandrill.bmp");
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(glGetUniformLocation(programID, "myTextureSampler"), 0);


	Obj3D hi = Obj3D("teapot.obj");
	time_t t_start = time(0);/*time(0)*/;
	time_t t_check;
	time_t needed;
	int frame_counter = 0;
	Szene1 szene1(&programID, &View, &Projection);


	const double maxFPS = 20.0;
	const double maxPeriod = 1.0 / maxFPS;
	double lastTime = 0.0;

	while (!glfwWindowShouldClose(window))
	{
	double timeLimiter = glfwGetTime();
double deltaTime = timeLimiter - lastTime;

if (deltaTime >= maxPeriod) {
	lastTime = timeLimiter;

	frame_counter += 1;
	t_check = time(0);
	needed = difftime(t_check, t_start);
	// * 100 damit wir time in milli sekunden bekommen, dadurch müssen wir aber auch frames *1000 rechnen, da Ursprungsgleichung: Gesamtframes / Gesamtzeit in Seconds
	if ((1000 * needed) != 0)
		std::cout << "current fps: " << ((frame_counter * 1000) / (1000 * needed)) << std::endl;

	// 1. Löschen des voherigen Bildes
	// Clear the screen und lösche z speicher
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 2. JETZT Erstellen des neuen Bildes (aka Rendern des neuen Bildes mit MVP-Prinzip (Model, View, Projection))

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units d.h. zwischen der Range von 0.1 bis 100 wird alles angezeigt
	// Parameter: 1.: wie weit ist Würfel hinten, 2. Seitenverhältnis, 3.  + 4. kA
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
	//Model = glm::rotate(Model, 25.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	Model = glm::rotate(Model, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
	Model = glm::rotate(Model, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::rotate(Model, angle_z, glm::vec3(0.0f, 0.0f, 1.0f));

	// skaliert alles
	Model = glm::scale(Model, glm::vec3(0.5, 0.5, 0.5));
	// senden an den Vertex-Shader
	// sendet MVP Matrix zum Vertex-Shader, erst die MVP-Matrix im Vertex-Shader beeinflusst zukünftig gezeichnete Objekte, Sinn: Wenn jetzt was geprintet wird, wird eben Vertex MVP-Matrix drauf angewandt, sonst nicht
	sendMVP();

	Szene2 szene2(&programID, &View, &Projection);
	//szene1.drawSzene(1);
	szene2.drawSzene(1);


	drawCS();
	//drawBalken();
	//drawSzene2(1.0f);


	// Swap buffers
	glfwSwapBuffers(window);
	// gettet alle Events und ruft eventuell Callback auf falls individuell vorhanden
	glfwPollEvents();
}

	} 

	glDeleteProgram(programID);
	// Cleanup VBO and shader
	glDeleteTextures(1, &Texture);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

