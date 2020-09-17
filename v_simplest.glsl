#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color; //kolor związany z wierzchołkiem
in vec4 normal; //wektor normalny w przestrzeni modelu
in vec2 texCoord0; //wsp teksturowania



//Zmienne interpolowane
out vec4 ic;    // przesłanie koloru do fragment shadera
out vec4 l;
out vec4 n;
out vec4 v;
out vec2 iTexCoord0;

void main(void) {
    vec4 lp = vec4(0, 200, 200, 1); //pozcyja światła, przestrzeń świata
    vec4 temp = V * M * vertex;
    l = normalize(V * lp - temp); //wektor do światła w przestrzeni oka
    v = normalize(vec4(0, 0, 0, 1) - temp); //wektor do obserwatora w przestrzeni oka
    n = normalize(V * M * normal); //wektor normalny w przestrzeni oka
    iTexCoord0 = texCoord0;

    ic = color;
    
    gl_Position=P*V*M*vertex;
}
