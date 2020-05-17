#pragma once
#include "math.h"
#include <iostream>


class mapGenerator {

private:
	const int flatness; //the bigger the more hilly
	const int size; //base of the map will be a square
	const int verticesCount;

	float** mapHeights;
	float* mapVertices;
	float* mapColors;
	float* mapNormals;

	void calculateMapHeights();
	void calculateMapVertices();
	void calculateNormals();
	void calculateColors();



public:
	mapGenerator(int flatness, int size);

	float* getVertices() { return mapVertices; }
	float* getNormals() { return mapNormals; }
	float* getColors() { return mapColors; }
	int getVertexCount() { return verticesCount; }


};