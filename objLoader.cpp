#include "objLoader.hpp"
#include <stdio.h>
#include <stdlib.h>


//MK

int loadOBJ(
	const char* path,
	float*& good_vertices,
	float*& good_texCoords,
	float*& good_normals,
	float*& good_colors
) {

	std::vector <glm::vec3> out_vertices;
	std::vector <glm::vec2> out_uvs;
	std::vector <glm::vec3> out_normals;


	std::vector <unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector <glm::vec3> temp_vertices;
	std::vector <glm::vec2> temp_uvs;
	std::vector <glm::vec3> temp_normals;

	FILE* file = NULL;
	fopen_s(&file, path, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! \n");
		return -1;
	}
	while (1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) break;
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by this parser!\n");
				return -1;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}

	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}

	good_vertices = new float[out_vertices.size() * 4];
	good_normals = new float[out_normals.size() * 4];
	good_texCoords = new float[out_uvs.size() * 2];
	good_colors = new float[out_vertices.size() * 4];
	int k = 0;
	for (int i = 0; i < out_vertices.size(); i++) {
		good_vertices[k] = out_vertices[i].x;
		good_vertices[k + 1] = out_vertices[i].y;
		good_vertices[k + 2] = out_vertices[i].z;
		good_vertices[k + 3] = 1.0f;
		k += 4;
	}
	k = 0;
	for (int i = 0; i < out_normals.size(); i++) {
		good_normals[k] = out_normals[i].x;
		good_normals[k + 1] = out_normals[i].y;
		good_normals[k + 2] = out_normals[i].z;
		good_normals[k + 3] = 0.0f;
		k += 4;
	}
	k = 0;
	for (int i = 0; i < out_uvs.size(); i++) {
		good_texCoords[k] = out_uvs[i].x;
		good_texCoords[k + 1] = out_uvs[i].y;
		k += 2;
	}
	k = 0;
	for (int i = 0; i < out_vertices.size(); i++) {
		good_colors[k] = 0.7f;
		good_colors[k + 1] = 1.0f;
		good_colors[k + 2] = 0.4f;
		good_colors[k + 3] = 1.0f;
		k += 4;
	}
	return out_vertices.size();
}