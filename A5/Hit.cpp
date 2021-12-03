#include "Hit.hpp"

Hit::Hit()
{}

Hit::~Hit()
{}

glm::vec3 Hit::Reflection(glm::vec3 V){
  return -2.0f*glm::dot(V,normal)*normal+V;
}

void Hit::copy(Hit hit0){
  pos=hit0.pos;
  normal=hit0.normal;
  U=hit0.U;
  V=hit0.V;
}
