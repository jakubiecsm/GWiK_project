#pragma once
#include "math.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "shaderprogram.h"


class mapGenerator {

private:
	const float flatness; //the bigger the more hilly
	const int size; //base of the map will be a square
	const int verticesCount;

	float** mapHeights;
	float* mapVertices;
	float* mapColors;
	float* mapNormals;
	float* texCoords;

	void calculateMapHeights();
	void calculateMapVertices();
	void calculateNormals();
	void calculateColors();
	void calculateTexCoords();



public:
	mapGenerator(float flatness, int size);

	void drawMap(ShaderProgram* sp, GLuint tex0);

	float* getVertices() { return mapVertices; }
	float* getNormals() { return mapNormals; }
	float* getColors() { return mapColors; }
	float* getTexCoords() { return texCoords; }
	int getVertexCount() { return verticesCount; }


};