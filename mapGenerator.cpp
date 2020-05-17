#include "mapGenerator.h"

mapGenerator::mapGenerator(int flatness, int size)
	: size(size), flatness(flatness), verticesCount(size * size * 6) {

	//Creating 2d array for storing heights in different map coords
	mapHeights = new float* [size + 1];
	for (int i = 0; i <= size; ++i)
		mapHeights[i] = new float[size + 1];

	//Creating array for storing walls (vertices)
	mapVertices = new float[4 * verticesCount]; //24 - one square contains 2 triangles, and 1 triangle consists of 3 vertices (4 coords each)

	//Creating array for storing walls normals
	mapNormals = new float[4 * verticesCount]; //same as above

	//Creating array for storing colors
	mapColors = new float[4 * verticesCount]; //same as above

	//Counting heights in different points of map
	calculateMapHeights();
	calculateMapVertices();
	calculateNormals();
	calculateColors();

}

void mapGenerator::calculateMapHeights() {

	//left bottom corner is set to1 [0][0] in array
	//x - rows, z - cols, y - heights
	//Function to calculate heights y = |z| + |x|

	int offsetX = size / 2;
	int offsetZ = size / 2;

	for (int z = 0; z <= size; ++z)
		for (int x = 0; x <= size; ++x)
			mapHeights[x][z] = abs(z - offsetZ) + abs(x - offsetX);
}

void mapGenerator::calculateMapVertices() {
	using namespace std;

	int index = 0;
	int offsetX = size / 2;
	int offsetZ = size / 2;

	for (int z = 0; z < size; ++z) {

		//One for creates two triangles (6 vertices = 24 coords)
		for (int x = 0; x < size; ++x) {
			
			//first triangle
			mapVertices[index++] = x - offsetX;
			mapVertices[index++] = mapHeights[z][x];
			mapVertices[index++] = z - offsetZ;
			mapVertices[index++] = 1.0f;

			mapVertices[index++] = x - offsetX + 1;
			mapVertices[index++] = mapHeights[z][x + 1];
			mapVertices[index++] = z - offsetZ;
			mapVertices[index++] = 1.0f;

			mapVertices[index++] = x - offsetX;
			mapVertices[index++] = mapHeights[z + 1][x];
			mapVertices[index++] = z - offsetZ + 1;
			mapVertices[index++] = 1.0f;

			//second triangle
			mapVertices[index++] = x - offsetX + 1;
			mapVertices[index++] = mapHeights[z][x + 1];
			mapVertices[index++] = z - offsetZ;
			mapVertices[index++] = 1.0f;

			mapVertices[index++] = x - offsetX;
			mapVertices[index++] = mapHeights[z + 1][x];
			mapVertices[index++] = z - offsetZ + 1;
			mapVertices[index++] = 1.0f;

			mapVertices[index++] = x - offsetX + 1;
			mapVertices[index++] = mapHeights[z + 1][x + 1];
			mapVertices[index++] = z - offsetZ + 1;
			mapVertices[index++] = 1.0f;
		}
	}

	/*for (int i = 0; i < 4 * verticesCount; i++) {
		if (i % 4 == 0) {
			cout << endl;
			if (i % 12 == 0) {
				cout << endl;
				cout << "triangle " << i / 12 + 1 << endl;
			}
		}
		
		cout << mapVertices[i] << "\t";

	}*/
}

void mapGenerator::calculateNormals() {
	using namespace std;

	for (int i = 0; i < 4 * verticesCount; i++) {
		cout << i << "|";
		mapNormals[i++] = 0.0f;
		mapNormals[i++] = 0.0f;
		mapNormals[i++] = 1.0f;
		mapNormals[i] = 0.0f;
	}

	//printing out
	/*for (int j = 0; j < 4 * verticesCount; j++) {
		if (j % 4 == 0) cout << endl;
		cout << mapNormals[j];
	}*/
		
}

void mapGenerator::calculateColors() {
	using namespace std;
	for (int i = 0; i < 4 * verticesCount; i++) {
		mapColors[i++] = 0.0f;
		mapColors[i++] = 1.0f;
		mapColors[i++] = 0.0f;
		mapColors[i] = 1.0f;
	}

	//printing out
	/*for (int j = 0; j < 4 * verticesCount; j++) {
		if (j % 4 == 0) cout << endl;
		cout << mapColors[j];
	}*/
}
