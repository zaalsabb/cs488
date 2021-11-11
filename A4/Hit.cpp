#include "Hit.hpp"

Hit::Hit()
{}

Hit::~Hit()
{}

glm::vec3 Hit::Reflection(glm::vec3 V){
  return -2.0f*glm::dot(V,n)*n+V;
}
