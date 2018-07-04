/////////////////////
//
//
//
// Grundidee: (also eig 1 VAO hat 1 VBO und 1 VBO hat 1 VAO) (1 VAO kann aber verschiedene Attribute haben, die sagen wie das VBO genutzt werden soll z.B. glVertexAttribPointer(0, 2 ----> 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0))
//
// 1.: Vertex Array Objects (VAOs) are conceptually nothing but thin state wrappers.
//
// 2.: Vertex Buffer Objects(VBOs) store actual data.
//
//	Another way of thinking about this is that VAOs describe the data stored in one or more VBOs.
//	Think of VBOs(and buffer objects in general) as unstructured arrays of data stored in server(GPU) memory.You can layout your vertex data in multiple arrays if you want, or you can pack them into a single array.In either case, buffer objects boil down to locations where you will store data.
//
//	VAO speichern: (deshalb bindet man diesen zuerst)
//	Aufrufe von glEnableVertexAttribArray or glDisableVertexAttribArray.
//	Konfigurationen von Vertex attributes via glVertexAttribPointer.
//	Vertex buffer objekte, die mit vertex attributes verbunden sind durch Aufrufe zu glVertexAttribPointer.
//
//
//
//Beispiel: (drauf achten wann man VBO und wann VAO benutzt)
//		unsigned int VBO, VAO;
//		glGenVertexArrays(1, &VAO); Erzeugung eines eindeutigen, der Grafikkarte bekannten, Speicherplatznamens (1 da man 1 haben will)
//		glGenBuffers(1, &VBO);
//// 		bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//		glBindVertexArray(VAO);
//
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); -> die 0 am Anfang bezieht sich auf die Position, die wir per location im vertexshader festgelegt haben
//		glEnableVertexAttribArray(0);
//
//// 		note that this is allowed; the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object, so afterwards we can safely unbind
//			(mit anderen Worten durch glVertexAttribPointer-Call wird das gebindete VBO als zugeh�rig zu dem vetex attribut erarchtet)
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//// 		You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
////		 VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//		glBindVertexArray(0);
//
//
//
//
//
//
//
//
//
//
/////////////////////



// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    DrahtWuerfel-Objekt
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint VertexArrayIDWireCube = 0;

static void createWireCube()
{
	// Vertexarrays kapseln ab OpenGL3 Eckpunkte, Texturen und Normalen
	glGenVertexArrays(1, &VertexArrayIDWireCube);
	glBindVertexArray(VertexArrayIDWireCube);

	//vertices == Eckpunkte
	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, -1.0f,-1.0f, 1.0f, 
		-1.0f, 1.0f,-1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,  1.0f,-1.0f, 1.0f,  
		 1.0f, 1.0f,-1.0f,  1.0f, 1.0f, 1.0f, 
		-1.0f,-1.0f,-1.0f, -1.0f, 1.0f,-1.0f, 
		-1.0f,-1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,  1.0f, 1.0f,-1.0f, 
		 1.0f,-1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  
		-1.0f,-1.0f,-1.0f,  1.0f,-1.0f,-1.0f,  
		-1.0f,-1.0f, 1.0f,  1.0f,-1.0f, 1.0f, 
		-1.0f, 1.0f,-1.0f,  1.0f, 1.0f,-1.0f, 
		-1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f
	};

	// Vertexbuffer-Daten z.B. auf Grafikkarte kopieren
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Erkl�ren wie die Vertex-Daten zu benutzen sind
	glEnableVertexAttribArray(0); // Kein Disable ausf�hren !
	glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

	glBindVertexArray(0);
}

void drawWireCube() // Kommentare muss in triangle stehen
{
	if (!VertexArrayIDWireCube) 
	{
		
		createWireCube();
	}
	
	glBindVertexArray(VertexArrayIDWireCube);
	
	glDrawArrays(GL_LINES, 0, 24); // 12 Linien haben 24 Punkte
	glBindVertexArray(0);
}


unsigned int createTriangle() {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f,  0.5f, 0.0f  // top   
	};

	float normals_triangle[]{
		0.0f,0.0f,-1.0f,
		0.0f,0.0f,-1.0f,
		0.0f,0.0f,-1.0
	};

	unsigned int VBO_vertices, VBO_normals, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_vertices);
	glGenBuffers(1, &VBO_normals);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(2);
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glEnableVertexAttribArray(2); // Kein Disable ausf�hren !
	glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals_triangle), normals_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);              // attribute. No particular reason for 2, but must match the layout in the shader. dort steht eben 2 f�r NormalBuffer


	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0); // 0 unbinds the vertex array
	
	return VAO;
}


void drawTriangle(unsigned int VAO) {
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0); // 0 unbinds the vertex array

}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Wuerfel-Objekt Bunt
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// das ist mein Container f�r alle Matrizen / Container
GLuint VertexArrayIDSolidCube = 0;

// brauchen wir nicht
static const GLfloat g_color_buffer_data[] = {
	0.583f,  0.771f,  0.014f,   0.609f,  0.115f,  0.436f,   0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,   0.435f,  0.602f,  0.223f,   0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,   0.559f,  0.436f,  0.730f,   0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,   0.559f,  0.861f,  0.639f,   0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,   0.771f,  0.328f,  0.970f,   0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,   0.971f,  0.572f,  0.833f,   0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,   0.945f,  0.719f,  0.592f,	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,	0.167f,  0.620f,  0.077f,	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,	0.714f,  0.505f,  0.345f,	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,	0.302f,  0.455f,  0.848f,	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,	0.053f,  0.959f,  0.120f,	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,	0.820f,  0.883f,  0.371f,	0.982f,  0.099f,  0.879f
};
static const GLfloat g_uv_tutorial[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
};

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, -1.0f,-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, // rechts hinten	// 1 Row = 1 Dreieck
	1.0f, 1.0f,-1.0f, -1.0f,-1.0f,-1.0f, -1.0f, 1.0f,-1.0f, // vorne rechts // 2 Reihen = 1 Cube-Seite			d.h. wir brauchen 6 (Seiten) * 2 Reihen f�r 1 Cube
	1.0f,-1.0f, 1.0f, -1.0f,-1.0f,-1.0f,  1.0f,-1.0f,-1.0f, // unten das rechte
	1.0f, 1.0f,-1.0f,  1.0f,-1.0f,-1.0f, -1.0f,-1.0f,-1.0f, // links vorne
	-1.0f,-1.0f,-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,-1.0f, // rechts das vordere (von eben rechts links)
	1.0f,-1.0f, 1.0f, -1.0f,-1.0f, 1.0f, -1.0f,-1.0f,-1.0f, // unten das linke
	-1.0f, 1.0f, 1.0f, -1.0f,-1.0f, 1.0f,  1.0f,-1.0f, 1.0f, // hinten rechts unten
	1.0f, 1.0f, 1.0f,  1.0f,-1.0f,-1.0f,  1.0f, 1.0f,-1.0f, // links das erste Dreieck
	1.0f,-1.0f,-1.0f,  1.0f, 1.0f, 1.0f,  1.0f,-1.0f, 1.0f, // links das hintere Dreieck
	1.0f, 1.0f, 1.0f,  1.0f, 1.0f,-1.0f, -1.0f, 1.0f,-1.0f, // oben das erste Dreieck
	1.0f, 1.0f, 1.0f, -1.0f, 1.0f,-1.0f, -1.0f, 1.0f, 1.0f, // oben das hintere Dreieck
	1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,  1.0f,-1.0f, 1.0f // hinten das links oben
};

// zu einer g_vertex Reihe(3 Punkte) brauchen wir also 1 Reihe g_normals (1 Punkt)
static const GLfloat g_normals[] = {
	// Punkte gesamt (1 Seite sind 2 Dreiecke): 6 ViereckSeiten * 2 Dreiecke pro Seite * 3 Punkte (wir brauchen ja pro Dreieck nur 1 Vektor, der 3 Koordinaten hat)
	// wir brauchen aus irgendeinen Grund doch f�r jeden einzelnen Triangle Punkt
	-1.0f,0.0f,0.0f, -1.0f,0.0f,0.0f,  -1.0f,0.0f,0.0f,

	0.0f,0.0f,-1.0f,  0.0f,0.0f,-1.0f,  0.0f,0.0f,-1.0f,

	0.0f,-1.0f,0.0f,  0.0f,-1.0f,0.0f,  0.0f,-1.0f,0.0f,

	0.0f,0.0f,-1.0f,  0.0f,0.0f,-1.0f,  0.0f,0.0f,-1.0f,

	-1.0f,0.0f,0.0f, -1.0f,0.0f,0.0f,  -1.0f,0.0f,0.0f, // rechts das vordere

	0.0f,-1.0f,0.0f,  0.0f,-1.0f,0.0f,  0.0f,-1.0f,0.0f,

	0.0f,0.0f,1.0f,  0.0f,0.0f,1.0f,  0.0f,0.0f,1.0f, // hinten rechts unten

	1.0f,0.0f,0.0f,  1.0f,0.0f,0.0f,  1.0f,0.0f,0.0f,

	1.0f,0.0f,0.0f,  1.0f,0.0f,0.0f,  1.0f,0.0f,0.0f,

	0.0f,1.0f,0.0f,  0.0f,1.0f,0.0f,  0.0f,1.0f,0.0f,

	0.0f,1.0f,0.0f,  0.0f,1.0f,0.0f,  0.0f,1.0f,0.0f,

	0.0f,0.0f,1.0f,  0.0f,0.0f,1.0f,  0.0f,0.0f,1.0f,



};

GLuint vertexbuffer;
// erstellt einen Buffer / Container f�r Farben des Objektes
// wird hier nicht direkt verwendet
GLuint colorbuffer;														// for texturing
GLuint normalbufferCube;





static void createCube()
{
	// erstellt einen Buffer / Container f�r Koordinaten des Objektes
	// wird hier nicht direkt verwendet

	
	// sagt, dass man alle Nutzdaten(versch. Objekte und Farben Daten) in einem Block bindet, damit man dann alles zusammen in den Vertex-Shader machen kann
	// also hier konkret wird per Pointer der Buffer in den Grafikspeicher geladen
	glGenVertexArrays(1, &VertexArrayIDSolidCube); // VAO // generiert Namen f�r dieses Array
	// hier konkret wird dieser Buffer an den Vortex buffer gebindet
	glBindVertexArray(VertexArrayIDSolidCube);

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

	// Nutzdaten, 12 Dreiecke mit ihren 3 Eckpunkten
	// solch eine Matrix muss f�r jedes Objekt einzeln existieren
	
	//------------------------------------------g_vertex_buffer_data ehemmals
	// insgesamt Laden der Nutzdaten in einen Buffer der Grafikkarten NICHT in den Vertex shader rein
	glGenBuffers(1, &vertexbuffer); // VBO	// hier wird das VBO also Vertex Buffer Object generiert: that can store a large number of vertices in the GPU's memory.
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); // hier wird VAO also Vertext Array Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); //?

	glGenBuffers(1, &normalbufferCube);
	glBindBuffer(GL_ARRAY_BUFFER, normalbufferCube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_normals), g_normals, GL_STATIC_DRAW);



	// One color for each vertex. They were generated randomly.
	// Farben
	// muss f�r jedes Objekt einzeln erstellt werden
	
	//-------------------------------------------g_color_buffer_data ehemals
	/*glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);*/



	glGenBuffers(1, &colorbuffer); // gibt 1 Speicherplatz f�r 1ne Variable
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer); // jetzt wird diese Variable benutzt
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_tutorial), g_uv_tutorial, GL_STATIC_DRAW); // jetzt wird der Speicherplatz gef�llt
	////////////////////7
	glEnableVertexAttribArray(0); // Kein Disable ausf�hren !
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);



	// 2nd attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glEnableVertexAttribArray(1); // Kein Disable ausf�hren !
	glVertexAttribPointer(
			1,                                // Kanal in den die Nutzdaten im Vortexshader eingef�hrt werdenattribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // Bildpunkte , size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // ?? stride
			(void*)0                          // array buffer offset
	);


	glBindBuffer(GL_ARRAY_BUFFER, normalbufferCube);
	glEnableVertexAttribArray(2); // Kein Disable ausf�hren !
	glVertexAttribPointer(
		2,                                // attribute. No particular reason for 2, but must match the layout in the shader. dort steht eben 2 f�r NormalBuffer
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	
	glBindVertexArray(0);
}

void set_things_up_after_print_words() {

	glBindVertexArray(VertexArrayIDSolidCube);
	glEnableVertexAttribArray(0); // muss enabled werden, da in print2d disabled wurde
	glEnableVertexAttribArray(1); // Kein Disable ausf�hren !
	glEnableVertexAttribArray(2); // Kein Disable ausf�hren !


}

void drawCube()
{
	if (!VertexArrayIDSolidCube) //Erstellen muss man nur beim ersten mal zeichnen machen
	{
		createCube();// legt Datenstruktur an
	}
	set_things_up_after_print_words();




	// Draw the triangles !
	// sagt, wo kommen die Daten her, + wie sind Daten aufgebaut, ...
	glBindVertexArray(VertexArrayIDSolidCube);
	// (wie viele Punkte gezeichnet werden m�ssen -> 12 Dreiecke a 3 Punkte
	glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles
	
	glBindVertexArray(0); // important!; Why? -> to unbind Vertex-Array, otherwise there will be some cool random stuff


}

void drawCubeWithBlending()
{

	if (!VertexArrayIDSolidCube) //Erstellen muss man nur beim ersten mal zeichnen machen
	{
		createCube();// legt Datenstruktur an
	}

	// Draw the triangles !
	// sagt, wo kommen die Daten her, + wie sind Daten aufgebaut, ...
	glBindVertexArray(VertexArrayIDSolidCube);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //GL_ONE_MINUS_DST_COLOR


	// (wie viele Punkte gezeichnet werden m�ssen -> 12 Dreiecke a 3 Punkte
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles
	glDisable(GL_BLEND);
	glBindVertexArray(0); // very important
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Kugel-Objekt
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint VertexArrayIDSphere = 0;
GLuint lats;
GLuint longs;


// Dieser Code  basiert auf http://ozark.hendrix.edu/~burch/cs/490/sched/feb8/
static void createSphere()
{
	glGenVertexArrays(1, &VertexArrayIDSphere);
	glBindVertexArray(VertexArrayIDSphere);

	static GLuint sphereVertexBuffer = 0;
	static GLfloat* sphereVertexBufferData = NULL;
	static GLfloat* sphereNormalBufferData = NULL;

	sphereVertexBufferData = new GLfloat [6 * (lats + 1) * (longs + 1)];
	sphereNormalBufferData = new GLfloat [6 * (lats + 1) * (longs + 1)];
	int index = 0;

    for (int i = 0; i <= lats; i++) 
	{
          GLfloat lat0 = (GLfloat) M_PI * ((GLfloat) -0.5 + (GLfloat) (i - 1) / (GLfloat) lats);
          GLfloat z0  = sin(lat0);
          GLfloat zr0 =  cos(lat0);
    
          GLfloat lat1 = (GLfloat) M_PI * ((GLfloat) -0.5 + (GLfloat) i / (GLfloat) lats);
          GLfloat z1 = sin(lat1);
          GLfloat zr1 = cos(lat1);
    
		  for (int j = 0; j <= longs; j++)
		  {
              GLfloat lng = (GLfloat) 2 * (GLfloat) M_PI * (GLfloat) (j - 1) / (GLfloat) longs;
              GLfloat x = cos(lng);
              GLfloat y = sin(lng);

			  sphereNormalBufferData[index] = x * zr0;
			  sphereVertexBufferData[index++] = x * zr0;
			  sphereNormalBufferData[index] = y * zr0;
			  sphereVertexBufferData[index++] = y * zr0;
			  sphereNormalBufferData[index] = z0;
			  sphereVertexBufferData[index++] = z0;
			  sphereNormalBufferData[index] = x * zr1;
			  sphereVertexBufferData[index++] = x * zr1;
			  sphereNormalBufferData[index] = y * zr1;
			  sphereVertexBufferData[index++] = y * zr1;
			  sphereNormalBufferData[index] = z1;
			  sphereVertexBufferData[index++] = z1;
          }

     }

	GLuint vertexbuffer;
	GLuint normalbuffer;
	
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * (lats + 1) * (longs + 1), sphereVertexBufferData, GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * (lats + 1) * (longs + 1), sphereNormalBufferData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Kein Disable ausf�hren !
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : normals
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glEnableVertexAttribArray(2); // Kein Disable ausf�hren !
	glVertexAttribPointer(
			2,                                // attribute. No particular reason for 2, but must match the layout in the shader. dort steht eben 2 f�r NormalBuffer
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
	);

	glBindVertexArray(0);
}

// Nur die Angabe bei der ersten Kugel ist relevant
void drawSphere(GLuint slats, GLuint slongs)
{
	if (!VertexArrayIDSphere)
	{
		lats = slats;
		longs = slongs;
		createSphere();
	}

	glBindVertexArray(VertexArrayIDSphere);
	// Draw the triangles !
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 2 * (lats + 1) * (longs + 1)); 
	glBindVertexArray(0);

}
