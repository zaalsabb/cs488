#include "Bump.hpp"

Bump::Bump(const std::string& fname ) : m_fname(fname) {}

Bump::~Bump() {
}

void Bump::loadBump(){
  image->loadPng(m_fname,1);
}

glm::vec3 Bump::getDepth(int x, int y){
  double r = image->getPixelValue(x,y,0);
  double g = image->getPixelValue(x,y,1);
  double b = image->getPixelValue(x,y,2);
  return glm::vec3(r,g,b);
}
