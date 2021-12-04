#include "Bump.hpp"
using namespace glm;

Bump::Bump(const std::string& fname ) : m_fname(fname) {}

Bump::~Bump() {
}

void Bump::loadBump(){
  image->loadPng(m_fname,3);
}

float Bump::getDepth(int x, int y){
  double d = image->getPixelValue(x,y,0);
  return d;
}

vec2 Bump::gradient(int x, int y){
  float Fu=0;
  float Fv=0;

  if (x>1 & x < image->width()-1 & y>1 & y < image->height()-1){
    Fu = (getDepth(x+1, y)-getDepth(x-1, y))/2;
    Fv = (getDepth(x, y+1)-getDepth(x, y-1))/2;
    // std::cout << x << " "<< y << "\n" << std::endl;
    // getDepth(x,y);
  }

  return -vec2(Fu,Fv);
}

void Bump::perturbNormal(int x, int y, Hit &hit){

  vec2 F = gradient(x,y);
  float Fu = F[0]*100;
  float Fv = F[1]*100;

  // if (Fu!=0 & Fv!=0){
  hit.normal = normalize(hit.normal+(Fu*cross(hit.normal,hit.Pu)+Fv*cross(hit.normal,hit.Pv))/length(hit.normal));
  // }
}
