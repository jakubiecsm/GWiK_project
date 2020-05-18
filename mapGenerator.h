#pragma once
#include "math.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


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

	float* getVertices() { return mapVertices; }
	float* getNormals() { return mapNormals; }
	float* getColors() { return mapColors; }
	float* getTexCoords() { return texCoords; }
	float** getMapHeights() { return mapHeights; }
	int getVertexCount() { return verticesCount; }


};