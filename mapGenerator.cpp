#include "mapGenerator.h"

mapGenerator::mapGenerator(float flatness, int size)
	: size(size), flatness(flatness), verticesCount(size * size * 6) {

	//Creating 2d array for storing heights in different map coords
	mapHeights = new float* [size + 1];
	for (int i = 0; i <= size; ++i)
		mapHeights[i] = new float[size + 1];

	//Creating array for storing walls (vertices)
	mapVertices = new float[4 * verticesCount]; //24 - one square contains 2 triangles, and 1 triangle consists of 3 vertices (4 coords each)

	//Creating array for storing walls normals
	mapNormals = new float[4 * verticesCount]; //same as above

	//Creating array for storing vertex normals
	mapVerticesNormals = new float[4 * verticesCount];

	//Creating array for storing colors
	mapColors = new float[4 * verticesCount]; //same as above

	//Creating array for storing texCoords
	texCoords = new float[2 * verticesCount]; //same as above

	//Counting heights in different points of map
	calculateMapHeights();
	calculateMapVertices();
	calculateMapNormals();
	calculateMapVerticesNormals();

	calculateMapColors();
	calculateMapTexCoords();

}

void mapGenerator::calculateMapHeights() {

	//left bottom corner is set to1 [0][0] in array
	//x - rows, z - cols, y - heights

	for (int z = 0; z <= size; ++z)
		for (int x = 0; x <= size; ++x)
			mapHeights[x][z] = 20 * flatness * (2 * cos(0.3 * x) * cos(0.3 * z));
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
}

void mapGenerator::calculateMapNormals() {
	using namespace std;
	using namespace glm;

	bool odd = true;
	vec3 v1, v2, v3;
	for (int i = 0; i < 4 * verticesCount; i++) {
		v1 = vec3(mapVertices[i + 4] - mapVertices[i],
			mapVertices[i + 5] - mapVertices[i + 1],
			mapVertices[i + 6] - mapVertices[i + 2]);
		v2 = vec3(mapVertices[i + 8] - mapVertices[i],
			mapVertices[i + 9] - mapVertices[i + 1],
			mapVertices[i + 10] - mapVertices[i + 2]);

		if (!odd) {
			v3 = normalize(cross(v1, v2));
			odd = true;
		}
		else {
			v3 = normalize(cross(v2, v1));
			odd = false;
		}
		
		for (int j = i; j < i + 12; j++) {
			mapNormals[j++] = v3.x;
			mapNormals[j++] = abs(v3.y);
			mapNormals[j++] = v3.z;
			mapNormals[j] = 0.0f;
		}
		i += 11;
	}
}


void mapGenerator::assingMapVerticesNormal(int vertex) {
	using namespace glm;

	vec3 temp = vec3(0, 0, 0);
	int anotherVertex = (size - 1) * 6 + 2;

	int moves[6] = { 0, 3, 5, anotherVertex, anotherVertex + 2, anotherVertex + 5 };

	//std::cout << "VEC3: " << temp.x << "|" << temp.y << "|" << temp.z << "\n";
	
	for (int i = 0; i < 6; i++) 
		temp += vec3(mapNormals[(vertex + moves[i]) * 4], mapNormals[(vertex + moves[i]) * 4 + 1], mapNormals[(vertex + moves[i]) * 4 + 2]);
	
	temp = normalize(temp);

	for (int i = 0; i < 6; i++) {
		mapVerticesNormals[(vertex + moves[i]) * 4] = temp.x;
		mapVerticesNormals[(vertex + moves[i]) * 4 + 1] = temp.y;
		mapVerticesNormals[(vertex + moves[i]) * 4 + 2] = temp.z;
	}
}

void mapGenerator::calculateMapVerticesNormals() {
	using namespace std;
	using namespace glm;

	for (int i = 0; i < 4 * verticesCount; i++) {
		mapVerticesNormals[i++] = 0.0f;
		mapVerticesNormals[i++] = 1.0f;
		mapVerticesNormals[i++] = 0.0f;
		mapVerticesNormals[i] = 0.0f;
	}

	int vertex = 5;
	int row = 1;
	while (vertex <= (6 * size * (size - 1) - 2)) {

		while (vertex < row * size * 6 - 1) {
			assingMapVerticesNormal(vertex);
			vertex += 6;
		}
		vertex -= 6;
		vertex = 5 + 6 * size * row;
		row++;
	}
}

void mapGenerator::calculateMapColors() {
	using namespace std;
	for (int i = 0; i < 4 * verticesCount; i++) {
		mapColors[i++] = 0.0f;
		mapColors[i++] = 1.0f;
		mapColors[i++] = 0.0f;
		mapColors[i] = 1.0f;
	}
}

void mapGenerator::calculateMapTexCoords() {
	for (int i = 0; i < 2 * verticesCount; i++) {
		texCoords[i++] = 0.0f;
		texCoords[i++] = 0.0f;

		texCoords[i++] = 0.0f;
		texCoords[i++] = 1.0f;

		texCoords[i++] = 1.0f;
		texCoords[i++] = 0.0f;

		texCoords[i++] = 1.0f;
		texCoords[i++] = 1.0f;

		texCoords[i++] = 0.0f;
		texCoords[i++] = 1.0f;

		texCoords[i++] = 1.0f;
		texCoords[i] = 0.0f;
	}

}
