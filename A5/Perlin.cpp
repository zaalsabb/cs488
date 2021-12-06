#include "Perlin.hpp"
#include <glm/ext.hpp>

using namespace glm;

//---------------------------------------------------------------------------------------
Perlin::Perlin()
{

}

//---------------------------------------------------------------------------------------
Perlin::~Perlin() {

}

double Perlin::perlinNoise(float x, float y, float octave){
  x=x/(float)octave;
  y=y/(float)octave;
	int xi = (int)std::floor(x) % 256;
	int yi = (int)std::floor(y) % 256;

  double xv = x - xi;
	double yv = y - yi;

  vec2 v1 = vec2(xv-1.0, yv-1.0);
	vec2 v2 = vec2(xv, yv-1.0);
	vec2 v3 = vec2(xv-1.0, yv);
	vec2 v4 = vec2(xv, yv);

  int s1 = seed[seed[xi+1]+yi+1];
	int s2 = seed[seed[xi]+yi+1];
	int s3 = seed[seed[xi+1]+yi];
	int s4 = seed[seed[xi]+yi];

  double h1 = dot(v1,TableToVector(s1));
	double h2 = dot(v2,TableToVector(s2));
	double h3 = dot(v3,TableToVector(s3));
	double h4 = dot(v4,TableToVector(s4));

  double u = Fade(xv);
	double v = Fade(yv);

  // std::cout << h1 << std::endl;

	return Lerp(u,
		     Lerp(v, h4, h2),
		     Lerp(v, h3, h1));

}

vec2 Perlin::TableToVector(int n){

	int q = n % 3;
	if(q == 0){
		return vec2(1.0, 1.0);
	} else if(q == 1) {
		return vec2(-1.0, 1.0);
	} else if(q == 2) {
		return vec2(-1.0, -1.0);
	} else {
		return vec2(1.0, -1.0);
  }
}

double Perlin::Fade(double t){
	return ((6*t - 15)*t + 10)*t*t*t;
}

double Perlin::Lerp(double t, double a, double b){
	return a + t*(b-a);
}
