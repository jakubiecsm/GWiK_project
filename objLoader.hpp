#ifndef OBJLOADER_H
#define OBJLOADER_H

//MK

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

int loadOBJ(
	const char* path,
	float*& good_vertices,
	float*& good_texCoords,
	float*& good_normals,
	float*& good_colors
);


#endif