#pragma once
class Obj3D
{
	GLuint vertexArrayID;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	GLuint normalbuffer; // Hier alles analog f�r Normalen in location == 2
	GLuint uvbuffer; // Hier alles analog f�r Texturkoordinaten in location == 1 (2 floats u und v!)
	GLuint vertexbuffer;

public:
	Obj3D(const char* fn); // Konstruktor
	void display();
	~Obj3D(); // Destruktor
};

