#include "Texture.hpp"

Texture::Texture(const std::string& fname ) : m_fname(fname) {}

Texture::~Texture() {
}

void Texture::loadTexture(){
  image->loadPng(m_fname,3);
}

glm::vec3 Texture::getColor(int x, int y){
  double r = image->getPixelValue(x,y,0);
  double g = image->getPixelValue(x,y,1);
  double b = image->getPixelValue(x,y,2);
  return glm::vec3(r,g,b);
}
