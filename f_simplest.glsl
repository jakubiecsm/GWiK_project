#version 330
uniform sampler2D textureMap0;
uniform sampler2D textureMap1;
out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela
in vec4 ic; 
in vec4 n;
in vec4 l[2];
in vec4 v;
in vec2 iTexCoord0;

void main(void) {
	//Znormalizowane interpolowane wektory
	vec4 ml0 = normalize(l[0]);
	vec4 ml1 = normalize(l[1]);
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);
	//Wektor odbity
	vec4 mr0 = reflect(-ml0, mn);
	vec4 mr1 = reflect(-ml1, mn);
	//Parametry powierzchni
	//vec4 kd = ic;
	vec4 kd = texture(textureMap0, iTexCoord0);
	vec4 ks = texture(textureMap1, iTexCoord0);
	//Obliczenie modelu oświetlenia
	float nl0 = clamp(dot(mn, ml0), 0, 1);
	float nl1 = clamp(dot(mn, ml1), 0, 1);
	float rv0 = pow(clamp(dot(mr0, mv), 0, 1), 50);
	float rv1 = pow(clamp(dot(mr1, mv), 0, 1), 50);
	pixelColor = vec4(kd.rgb * nl0, kd.a) + vec4(ks.rgb*rv0, 0);
	pixelColor += vec4(kd.rgb * nl1, kd.a) + vec4(ks.rgb*rv1, 0);
	//pixelColor = ic;
}