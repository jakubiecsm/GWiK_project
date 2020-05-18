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

	//Creating array for storing colors
	mapColors = new float[4 * verticesCount]; //same as above

	//Creating array for storing texCoords
	texCoords = new float[2 * verticesCount]; //same as above

	//Counting heights in different points of map
	calculateMapHeights();
	calculateMapVertices();
	calculateNormals();
	calculateColors();
	calculateTexCoords();

}

void mapGenerator::calculateMapHeights() {

	//left bottom corner is set to1 [0][0] in array
	//x - rows, z - cols, y - heights

	int offsetX = size / 2;
	int offsetZ = size / 2;

	for (int z = 0; z <= size; ++z)
		for (int x = 0; x <= size; ++x)
			mapHeights[x][z] = 20 * flatness * (cos(0.3 * x) * cos(0.3 * z));
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

void mapGenerator::calculateNormals() {
	using namespace std;

	glm::vec3 v1, v2, v3;
	for (int i = 0; i < 4 * verticesCount; i++) {
		v1 = glm::vec3(mapVertices[i + 4] - mapVertices[i],
			mapVertices[i + 5] - mapVertices[i + 1],
			mapVertices[i + 6] - mapVertices[i + 2]);
		v2 = glm::vec3(mapVertices[i + 8] - mapVertices[i],
			mapVertices[i + 9] - mapVertices[i + 1],
			mapVertices[i + 10] - mapVertices[i + 2]);

		v3 = glm::normalize(glm::cross(v1, v2));
		
		//cout << v3.x << "|" << v3.y << "|" << v3.z << endl;
		
		for (int j = i; j < 12; j++) {
			mapNormals[j++] = v3.x;
			mapNormals[j++] = v3.y;
			mapNormals[j++] = v3.z;
			mapNormals[j] = 0.0f;
		}
		i += 11;
	}
}

void mapGenerator::calculateColors() {
	using namespace std;
	for (int i = 0; i < 4 * verticesCount; i++) {
		mapColors[i++] = 0.0f;
		mapColors[i++] = 1.0f;
		mapColors[i++] = 0.0f;
		mapColors[i] = 1.0f;
	}
}

void mapGenerator::calculateTexCoords() {
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

void mapGenerator::drawMap(ShaderProgram* sp, GLuint tex0)
{
	glm::mat4 M = glm::mat4(1.0f);
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(sp->a("vertex"));  //W��cz przesy�anie danych do atrybutu vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, mapVertices); //Wska� tablic� z danymi dla atrybutu vertex

	glEnableVertexAttribArray(sp->a("color"));  //W��cz przesy�anie danych do atrybutu color
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, mapColors); //Wska� tablic� z danymi dla atrybutu color

	glEnableVertexAttribArray(sp->a("normal"));  //W��cz przesy�anie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, mapNormals); //Wska� tablic� z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord0"));  //W��cz przesy�anie danych do atrybutu texCoord
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords); //Wska� tablic� z danymi dla atrybutu texCoord

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);

	glDrawArrays(GL_TRIANGLES, 0, getVertexCount()); //Narysuj obiekt
	glDisableVertexAttribArray(sp->a("vertex"));  //Wy��cz przesy�anie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("color"));  //Wy��cz przesy�anie danych do atrybutu color
	glDisableVertexAttribArray(sp->a("normal"));  //Wy��cz przesy�anie danych do atrybutu normal
	glDisableVertexAttribArray(sp->a("texCoord0"));  //Wy��cz przesy�anie danych do atrybutu texCoord0
}