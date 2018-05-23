#define UEBUNG1 /* feste Rotation */
// Pflichtteil: Ergebnis zeigen ...
// Kode zeilenweise erklären. (Orientiert sich an http://www.opengl-tutorial.org/, Evtl. diese Tutorials dort ausführen, um zu vertiefen.)
// Dort wird glfw in der Version 2 genutzt, wir verwenden die aktuelle Version 3 http://www.glfw.org/
// Schwarze Linien wg. Shader. Kurz erklaeren, was die Shader machen...
// Vorgehensweise erklaeren, Jeweils alte cpp-Datei nach CGTutorial.cpp.n kopieren, damit jede Aenderung nachvollziehbar bleibt.
// Aufgabe Rotation: glm::rotate    (http://glm.g-truc.net/glm.pdf)

#define UEBUNG2 /* variable Rotation ueber R-Taste */
// Eventloop, kann man muss man aber nicht in glfw (Alternativ Glut, dort muss man)
// Aufgabe: Hinweis globale Variable, Taste...

#define UEBUNG3 /* Kamerasteuerung */
// Aufgabe drei Unabhängige Rotationen, wird zu erstem Teil des Pflichtteils
// Hinweis auf andere Kamerasteuerungen ->  http://www.opengl-tutorial.org

#define UEBUNG4 /* Ausgemaltes Objekt und Z-Buffer */
// OpenGL-Befehle: http://wiki.delphigl.com/index.php/Hauptseite auf Deutsch!
// GLEW http://glew.sourceforge.net/
// Wireframe vs. Solid thematisieren, Z-Buffer wird noetig, um Verdeckungsproblem zu lösen
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/

#define UEBUNG5 /* Einlesen eines Objekts */
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
// Bessere OBJ-Loader vorhanden, basieren aber auf OpenGL1.1
// Andere Formate möglich, z. B. 3ds, s. a. Link am Ende der Seite
// Wir nehmen Teapot, Anekdote zu Teapot:  von Newell 1975 (hat berühmtes Lehrbuch geschrieben) glut, 3dsmax, Toystory, Monster AG, ...
//
// Vertex Buffer Objects (VBO) (ab 1.5) enthalten alle Daten zu Oberflaechen eines Objekts (Eckpunktkoordinaten, Normalen, Texturkoordinaten -> Uebung 6)
// koennen in separatem Speicher einer Grafikkarte gehalten werden (haengt vom Modell ab)
// koennen ueber API-Aufrufe veraendert werden --> glBufferData, glMapBuffer (GL_STATIC_DRAW, um mitzuteilen, dass sich nichts aendern wird)
// Vertex Array Objects (VAO) (ab 3) kapseln mehrere VBOs eines Objects zwecks Optimierung und einfachrer Benutzung:
// Beim Zeichnen nur 2 Aufrufe: glBindVertexArray und glDrawArrays
//#define UEBUNG5TEDDY  /* Nach der Teddy-Übung fuer Uebung6 wieder ausschalten */
// Alternativ: Teddy wenn die Zeit reicht: google nach teddy chameleon, teapot.obj mit xxx.obj austauschen....
// Modellieren kann also auch einfach sein, Freies Tool Blender (open Source), Professionelle Werkzeuge Maya, 3dsmax, etc. (nicht gegenstand der LV)

#define UEBUNG6 /* Beleuchten, neuer Shader */
// Teddy-Modell hat keine Normalen, passt nicht zu Shadern, wieder zur Teekanne zurueck.
// Shader anschauen, Alter Shader "ColourFragmentShader" setzt Farbe direkt, wird interpoliert ("Gouraud-Shading")
// "TransformVertexShader" gibt Farben weiter, legt layout der Eingabe-Daten fest, verwendet MVP um Eckpunkte zu transvormieren ("Eine Matrix reicht")
// Neue Shader koennen mehr (Immer noch nicht, was die Fixed-Function-Pipeline konnte) 
// Normalen stehen senkrecht auf Oberflaechen, wichtig fuer die Beleuchtung
// Normalen muessen anders behandelt werden als Eckpunkte, deshalb Trennung von MVP in Model View Projection
// -> Shader verändern in Uebung 15

#define UEBUNG7 /* Texturieren */
// Farbtexturen sind digitale Rasterbilder (andere Texturen in Kombination moeglich "Multi-Texturing" nicht Gegenstand der Uebung -> VL Textur)
// Imageloader fuer png und jpg nicht in den Bibliotheken enthalten -> SOIL
// DDS-Format kompatibel zu Texturkompression der Hardware. Wir nehmen aber BMP !
// s. a.:  http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/, Achtung glfwLoadTexture2D gibt' nicht mehr in glfw-version 3
// Granularitaet: Textur pro Objekt. kann also gewechselt werden ! --> Uebung 8
// Texturierte Teekanne ist 2. Teil des Pflichtteils 
///////////////////////////////////////////////////////

#define UEBUNG8 /* Mehrere Objekte */
// Polygone bilden Objekt, Objekte haben eigene Transformationen ("Model"-Matrix) eigene Texturen, etc.
// VAOs abwechselnd binden, MVP-Matrizen abwechselnd setzen, ggf Texturen abwechselnd binden, OpenGL verwendet jeweils positive Zahlen als
// Namen, die man sich generieren lassen muss.
// Model-Matrix fuer jedes Objekt anders, Szenen haben meist hierarchische Struktur, Multiplikationskette von der Wurzel zum Blatt
// Roboter-Beispiel, um Ketten zu lernen

#define UEBUNG9 /* Koordinatenachse */
// Notwendigkeit Koordinatensysteme anzeigen zu lassen... -> drawCS-Funktion mit drei Balkenen
// Wie erhaelt man langen duennen Balken mit bekannten Geometrien ?
// Aufgabe: Balken (leider mit M, V, P, ... als Parameter) Hinweis ginge auch als Singleton...
// Skalierungsparameter ruhig ausprobieren.
// sieht man den Balken im Bauch der Teekanne ?

#define UEBUNG10 /* Koordinatenkreuz */
// Aufgabe: Drei Balken, spaeter entsteht die Notwendigkeit Matrizen zu sichern (evtl. Mechanismus von OpenGL1 erwaehnen)

#define UEBUNG11 /* Ein Robotersegment */
// Teekanne ausblenden, Kugel zeichnen, Transformationsreihenfolge nochmal thematisieren
// Aufgabe: -Funktion mit Parameter!

#define UEBUNG12 /* Drei Robotersegmente uebereinander */
// Aufgabe: statischer Roboter, Unterschied lokales vs. globales Translate

#define UEBUNG13 /* Rotationen in den Gelenken */
// Aufgabe Roboter mit Tastensteuerung, Reihenfolge der Transformationen von oben nach unten und umgekehrt mit Stiften erläutern

#define UEBUNG14 /* Lampe am Ende */
// Uebung 15 im StandardShading pixelshader
// Hier mal exemplarisch den Pixelshader aendern, um die Beleuchtung ansprechender zu machen
// Erwaehnen, dass man Parameter wie "MVP" kontrollieren koennte.
// Hier beginnt die Wellt der Shader-programmierung, die nicht Gegenstand der Uebung ist.
// Lampe am Ende eines steuerbaren Roboters ist dritter Teil des Pflichtteils
// (5 Punkte: 3 Rotationen, Teekanne, texturiert, Roboter, Licht am Ende) 


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






//Header: hier steht alles was man in cpp findet -> Funktionen
//Cpp-File: hier steht der Großteil der Implementierung

//0 = False; 1 = True

float angle_x = 0.0f;
float angle_y = 0.0f;
float angle_z = 0.0f;

float angle_haupt_arm_z = 0.0f;

float angle_middle_arm = 0.0f;
float angle_unter_arm = 0.0f;

float angle_haupt_arm_y = 0.0f;




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
	case GLFW_KEY_A:
		angle_haupt_arm_z += 5.0;
		break;
	case GLFW_KEY_S:
		angle_middle_arm += 5.0;
		break;
	case GLFW_KEY_D:
		angle_unter_arm += 5.0;
		break;
	case GLFW_KEY_F:
		angle_haupt_arm_y += 5.0;
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
	Model = glm::scale(Model, glm::vec3(10*1.0 / 1.0, 1.0 / 100.0, 1.0 / 100.0));
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

void drawSeg(float hight) {
	/*glm::mat4 Save = Model;
	Model = glm::translate(Model, glm::vec3(0.0, hight,0.0));
	Model = glm::scale(Model, glm::vec3(hight /5, hight, hight /5));
	sendMVP();
	drawSphere(10, 10);
	Model = Save;*/
	


	glm::mat4 Save = Model;
	Model = glm::translate(Model, glm::vec3(0.0f, hight/2.0f, 0.0f));
	Model = glm::scale(Model, glm::vec3(hight / 10.0f, hight/2.0f, hight / 10.0f));
	sendMVP();
	drawSphere(10, 10);
	Model = Save; 
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


	// Eventloop/Render-loop
	// was ist Rendern?
	// -> Der Computer berechnet vor endgültigen Fertigstellung die Effekte zur Nachbearbeitung, zum Beispiel die Schärfe, die Belichtung oder die Übergänge. Diese Berechnungen werden als Rendering bezeichnet.
	// Rendern = ca. die Berechnung der Bildpunkte eines neuen Bildes (Bildpunkte eines Objektes zum Beispiel)




	// Teekanne und Buffer laden
	// Datei Oräfixes:
	// v: vortex
	// vn: vortex normal
	// vt: texture
	// f: Kombination dieser 3

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("teapot.obj", vertices, uvs, normals);


	// GesamterBlock wird genau 1 mal ausgeführt
	// Jedes Objekt eigenem VAO zuordnen, damit mehrere Objekte moeglich sind
	// VAOs sind Container fuer mehrere Buffer, die zusammen gesetzt werden sollen.
	GLuint VertexArrayIDTeapot;
	glGenVertexArrays(1, &VertexArrayIDTeapot);
	glBindVertexArray(VertexArrayIDTeapot);

	// Ein ArrayBuffer speichert Daten zu Eckpunkten (hier xyz bzw. Position)
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer); // Kennung erhalten
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); // Daten zur Kennung definieren
												 // Buffer zugreifbar für die Shader machen
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);


	// Erst nach glEnableVertexAttribArray kann DrawArrays auf die Daten zugreifen...
	glEnableVertexAttribArray(0); // siehe layout im vertex shader: location = 0 
	glVertexAttribPointer(0,  // location = 0 
		3,  // Datenformat vec3: 3 floats fuer xyz 
		GL_FLOAT,
		GL_FALSE, // Fixedpoint data normalisieren ?
		0, // Eckpunkte direkt hintereinander gespeichert
		(void*)0); // abweichender Datenanfang ? 




	// Hier wird alles rund um den normalen Vektor gemacht -> berechnet, gespeichert, ...
	GLuint normalbuffer; // Hier alles analog für Normalen in location == 2
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2); // siehe layout im vertex shader 
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Festlegen der Position der Lichtquelle
	//glm::vec3 lightPos = glm::vec3(4, 4, -4);
	//glUniform3f(glGetUniformLocation(programID, "LightPosition_worldspace"), lightPos.x, lightPos.y, lightPos.z);





	GLuint uvbuffer; // Hier alles analog für Texturkoordinaten in location == 1 (2 floats u und v!)
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1); // siehe layout im vertex shader 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Load the texture
	//benoetigt 24 bit bmp picture
	GLuint Texture = loadBMP_custom("mandrill.bmp");




	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(glGetUniformLocation(programID, "myTextureSampler"), 0);



	while (!glfwWindowShouldClose(window))
	{
		// 1. Löschen des voherigen Bildes
		// Clear the screen und lösche z speicher
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		// 2. Erstellen des neuen Bildes (aka Rendern des neuen Bildes mit MVP-Prinzip (Model, View, Projection))

		//
		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units d.h. zwischen der Range von 0.1 bis 100 wird alles angezeigt
		// Parameter: 1.: wie weit ist Würfel hinten, 2. Seitenverhältnis, 3.  + 4. kA
		Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		
		// Wo steht Kamera
		// Camera matrix
		View = glm::lookAt(glm::vec3(0,0,-5), // Wo ist Kamera / Betrachter
						   glm::vec3(0,0,0),  // Wo schaut er hin
						   glm::vec3(0,1,0)); // Wo ist oben (damit man sicherstellt, dass Betrachter nicht schief guckt)


		
		// was passiert mit Objekten bezogen auf Welt
		// Model matrix : an identity matrix = Einheitsmatrix = Es passiert nichts = kein Einfluss ( ??= Am Ursprung?? -> war voheriger Kommentar)
		Model = glm::mat4(1.0f);

		//Model = glm::rotate(altes Model,Winkel, Vektor der die Achse aufspannt um den sich gedreht werden soll-> x=Daumen,y=Zeigefinger,z=Mittelfinger)
		//Model = glm::rotate(Model, 25.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		Model = glm::rotate(Model, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));

		Model = glm::rotate(Model,angle_x, glm::vec3(1.0f, 0.0f, 0.0f));

		Model = glm::rotate(Model, angle_z, glm::vec3(0.0f, 0.0f, 1.0f));


		// Schritte für Teekanne
		glm::mat4 Save = Model;
		Model = glm::translate(Model, glm::vec3(1.5, 0.0, 0.0));
		Model = glm::scale(Model, glm::vec3(1.0 / 1000.0, 1.0 / 1000.0, 1.0 / 1000.0));
		sendMVP();


		// zeichnen des eigentichen Bildes
		//drawCube();	


		// 4 //
		// Teekann zeichnen
		glBindVertexArray(VertexArrayIDTeapot);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());


		Model = Save;
		Model = glm::scale(Model, glm::vec3(0.5, 0.5, 0.5));
		// senden an den Vertex-Shader
		sendMVP();
		//drawSphere(10, 10);
		
		drawCS();
		Model = glm::rotate(Model, angle_haupt_arm_z, glm::vec3(0.0f, 0.0f, 1.0f));
		Model = glm::rotate(Model, angle_haupt_arm_y, glm::vec3(0.0f, 1.0f, 0.0f));
		drawSeg(1);
		Model = glm::translate(Model, glm::vec3(0, 1.0f, 0));
		Model = glm::rotate(Model, angle_middle_arm, glm::vec3(0.0f, 0.0f, 1.0f)); // wichtig: rotate after translate
		drawSeg(0.8f);
		Model = glm::translate(Model, glm::vec3(0, 0.8f, 0));
		Model = glm::rotate(Model, angle_unter_arm, glm::vec3(0.0f, 0.0f, 1.0f));
		drawSeg(0.5);
		glm::vec4 lightPos = Model * glm::vec4(0, 0.5,0,1);
		glUniform3f(glGetUniformLocation(programID, "LightPosition_worldspace"), lightPos.x, lightPos.y, lightPos.z);
		
		// Swap buffers
		glfwSwapBuffers(window);

		// gettet alle Events und ruft eventuell Callback auf falls individuell vorhanden
        glfwPollEvents();
	} 

	glDeleteProgram(programID);


	// 5 //

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);

	glDeleteBuffers(1, &normalbuffer);


	glDeleteBuffers(1, &uvbuffer);
	glDeleteTextures(1, &Texture);


	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

