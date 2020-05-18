/*
Niniejszy program jest wolnym oprogramowaniem; mo�esz go
rozprowadza� dalej i / lub modyfikowa� na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacj� Wolnego
Oprogramowania - wed�ug wersji 2 tej Licencji lub(wed�ug twojego
wyboru) kt�rej� z p�niejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej�, i� b�dzie on
u�yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domy�lnej
gwarancji PRZYDATNO�CI HANDLOWEJ albo PRZYDATNO�CI DO OKRE�LONYCH
ZASTOSOWA�.W celu uzyskania bli�szych informacji si�gnij do
Powszechnej Licencji Publicznej GNU.

Z pewno�ci� wraz z niniejszym programem otrzyma�e� te� egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
je�li nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#ifndef SPHERE_H
#define SPHERE_H



//Sphere model made out of triangles
//Contains arrays:
//vertices - vertex positions in homogenous coordinates
//normals - vertex normals in homogenous coordinates
//texCoords - texturing coordinates


#include "Model.h"
#include "shaderprogram.h"
namespace Models {

	using namespace std;
	using namespace glm;

	class Sphere : public Model {

	public:
		Sphere();
		Sphere(float r, float mainDivs, float tubeDivs);
		virtual ~Sphere();
		virtual void drawSolid(bool smooth = true);
		void draw(ShaderProgram * sp, GLuint tex0);

	private:
		vector<vec4> internalVertices;
		vector<vec4> internalFaceNormals;
		vector<vec4> internalVertexNormals;

		inline float d2r(float deg);
		vec4 generateSpherePoint(float r, float alpha, float beta);
		vec4 computeVertexNormal(float alpha, float beta);
		vec4 computeFaceNormal(vector<vec4>& face);
		void generateSphereFace(vector<vec4>& vertices, vector<vec4>& vertexNormals, vec4& faceNormal, float r, float alpha, float beta, float step_alpha, float step_beta);
		void buildSphere(float r, float divs1, float divs2);

	};

	extern Sphere sphere;

}

#endif
