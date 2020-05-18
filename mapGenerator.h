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
	float* mapVerticesNormals;
	float* texCoords;

	void calculateMapHeights();
	void calculateMapVertices();
	void calculateMapNormals();
	void calculateMapVerticesNormals();
	void calculateMapColors();
	void calculateMapTexCoords();



public:
	mapGenerator(float flatness, int size);

	float* getMapVertices() { return mapVertices; }
	float* getMapNormals() { return mapNormals; }
	float* getMapVerticesNormals() { return mapVerticesNormals; }
	float* getMapColors() { return mapColors; }
	float* getMapTexCoords() { return texCoords; }
	float** getMapHeights() { return mapHeights; }
	int getMapVertexCount() { return verticesCount; }


};