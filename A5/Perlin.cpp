#include "Perlin.hpp"
#include <glm/ext.hpp>

using namespace glm;

//---------------------------------------------------------------------------------------
Perlin::Perlin(float noise)
  : m_noise(noise)
{

}

//---------------------------------------------------------------------------------------
Perlin::~Perlin() {

}


// float Fade(float t){
// 	return ((6*t - 15)*t + 10)*t*t*t;
// }

// float Lerp(float t, float a1, float a2){
// 	return a1 + t*(a2-a1);
// }

float Perlin::noise_normal(float x, float y, int sx, int sy, glm::vec3 &normal){
	int x_i = (int)std::floor(x/(float)sx * 255);
	int y_i = (int)std::floor(y/(float)sy * 255);

	// std::cout << x << std::endl;
	float p = (float)seed[x_i + y_i] / 256.0f * m_noise;
	
	return p;

}

