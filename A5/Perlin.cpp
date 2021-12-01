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

float Perlin::noise_function(float x, float y){
	int x_i = (int)std::max(std::floor(x * 255),1);
	int y_i = (int)std::max(std::floor(y * 255),1);
	
	return (float)seed[x_i + y_i] / m_noise;

}
