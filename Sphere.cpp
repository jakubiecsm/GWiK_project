/*
Niniejszy program jest wolnym oprogramowaniem; mo¿esz go
rozprowadzaæ dalej i / lub modyfikowaæ na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacjê Wolnego
Oprogramowania - wed³ug wersji 2 tej Licencji lub(wed³ug twojego
wyboru) którejœ z póŸniejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej¹, i¿ bêdzie on
u¿yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyœlnej
gwarancji PRZYDATNOŒCI HANDLOWEJ albo PRZYDATNOŒCI DO OKREŒLONYCH
ZASTOSOWAÑ.W celu uzyskania bli¿szych informacji siêgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnoœci¹ wraz z niniejszym programem otrzyma³eœ te¿ egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeœli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#include "Sphere.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>


namespace Models {

	Sphere sphere;

	Sphere::Sphere() {
		buildSphere(1, 12, 12);
	}

	Sphere::Sphere(float r, float divs1, float divs2) {
		buildSphere(r, divs1, divs2);
	}

	Sphere::~Sphere() {
	}

	inline float Sphere::d2r(float deg) {
		return PI * deg / 180.0f;
	}

	vec4 Sphere::generateSpherePoint(float r, float alpha, float beta) {
		alpha = d2r(alpha);
		beta = d2r(beta);
		return vec4(r * cos(alpha) * cos(beta), r * cos(alpha) * sin(beta), r * sin(alpha), 1.0f);
	}

	vec4 Sphere::computeVertexNormal(float alpha, float beta) {
		alpha = d2r(alpha);
		beta = d2r(beta);
		return vec4(cos(alpha) * cos(beta), cos(alpha) * sin(beta), sin(alpha), 0.0f);
	}

	vec4 Sphere::computeFaceNormal(vector<vec4>& face) {
		vec3 a = vec3(face[1] - face[0]);
		vec3 b = vec3(face[2] - face[0]);

		return normalize(vec4(cross(b, a), 0.0f));
	}

	void Sphere::generateSphereFace(vector<vec4>& vertices, vector<vec4>& vertexNormals, vec4& faceNormal, float r, float alpha, float beta, float step_alpha, float step_beta) {
		vertices.clear();
		vertexNormals.clear();

		vertices.push_back(generateSpherePoint(r, alpha, beta));
		vertices.push_back(generateSpherePoint(r, alpha + step_alpha, beta));
		vertices.push_back(generateSpherePoint(r, alpha + step_alpha, beta + step_beta));
		vertices.push_back(generateSpherePoint(r, alpha, beta + step_beta));

		faceNormal = computeFaceNormal(vertices);

		vertexNormals.push_back(computeVertexNormal(alpha, beta));
		vertexNormals.push_back(computeVertexNormal(alpha + step_alpha, beta));
		vertexNormals.push_back(computeVertexNormal(alpha + step_alpha, beta + step_beta));
		vertexNormals.push_back(computeVertexNormal(alpha, beta + step_beta));
	}



	void Sphere::buildSphere(float r, float mainDivs, float tubeDivs) {
		vector<vec4> face;
		vector<vec4> faceVertexNormals;
		vec4 normal;

		internalVertices.clear();
		internalFaceNormals.clear();
		internalVertexNormals.clear();

		float mult_alpha = 180.0f / tubeDivs;
		float mult_beta = 360.0f / mainDivs;

		for (int alpha = 0; alpha < round(tubeDivs); alpha++) {
			for (int beta = 0; beta < round(mainDivs); beta++) {

				generateSphereFace(face, faceVertexNormals, normal, r, alpha * mult_alpha - 90.0f, beta * mult_beta, mult_alpha, mult_beta);

				internalVertices.push_back(face[0]);
				internalVertices.push_back(face[1]);
				internalVertices.push_back(face[2]);

				internalVertices.push_back(face[0]);
				internalVertices.push_back(face[2]);
				internalVertices.push_back(face[3]);

				internalVertexNormals.push_back(faceVertexNormals[0]);
				internalVertexNormals.push_back(faceVertexNormals[1]);
				internalVertexNormals.push_back(faceVertexNormals[2]);

				internalVertexNormals.push_back(faceVertexNormals[0]);
				internalVertexNormals.push_back(faceVertexNormals[2]);
				internalVertexNormals.push_back(faceVertexNormals[3]);

				for (int i = 0; i < 6; i++) internalFaceNormals.push_back(normal);


			}
		}

		vertices = (float*)internalVertices.data();
		normals = (float*)internalFaceNormals.data();
		vertexNormals = (float*)internalVertexNormals.data();
		texCoords = vertexNormals;
		vertexCount = internalVertices.size();
	}

	void Sphere::drawSolid(bool smooth) {

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//glEnableVertexAttribArray(3);


		glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertices);
		if (!smooth) glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normals);
		else glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, vertexNormals);
		glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, texCoords);
		//glVertexAttribPointer(3,4,GL_FLOAT,false,0,Models::CubeInternal::colors);

		glDrawArrays(GL_TRIANGLES, 0, vertexCount);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		//glDisableVertexAttribArray(3);

	}

	void Sphere::draw(ShaderProgram *sp, GLuint tex0)
	{
		glm::mat4 M = glm::mat4(1.0f);
		M = glm::translate(M, glm::vec3(0.0f, 0.0f, 10.0f));
		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

		glEnableVertexAttribArray(sp->a("vertex"));  //W³¹cz przesy³anie danych do atrybutu vertex
		glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, vertices); //Wska¿ tablicê z danymi dla atrybutu vertex

		glEnableVertexAttribArray(sp->a("color"));  //W³¹cz przesy³anie danych do atrybutu color
		glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors); //Wska¿ tablicê z danymi dla atrybutu color

		glEnableVertexAttribArray(sp->a("normal"));  //W³¹cz przesy³anie danych do atrybutu normal
		glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, normals); //Wska¿ tablicê z danymi dla atrybutu normal

		glEnableVertexAttribArray(sp->a("texCoord0"));  //W³¹cz przesy³anie danych do atrybutu texCoord
		glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords); //Wska¿ tablicê z danymi dla atrybutu texCoord

		glDisableVertexAttribArray(sp->a("vertex"));  //Wy³¹cz przesy³anie danych do atrybutu vertex
		glDisableVertexAttribArray(sp->a("color"));  //Wy³¹cz przesy³anie danych do atrybutu color
		glDisableVertexAttribArray(sp->a("normal"));  //Wy³¹cz przesy³anie danych do atrybutu normal
		glDisableVertexAttribArray(sp->a("texCoord0"));  //Wy³¹cz przesy³anie danych do atrybutu texCoord0

		glUniform1i(sp->u("textureMap0"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex0);

		glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt
		glDisableVertexAttribArray(sp->a("vertex"));  //Wy³¹cz przesy³anie danych do atrybutu vertex
		glDisableVertexAttribArray(sp->a("color"));  //Wy³¹cz przesy³anie danych do atrybutu color
		glDisableVertexAttribArray(sp->a("normal"));  //Wy³¹cz przesy³anie danych do atrybutu normal
		glDisableVertexAttribArray(sp->a("texCoord0"));  //Wy³¹cz przesy³anie danych do atrybutu texCoord0
	
	}

}
