#pragma once

#include <glm/glm.hpp>

#include "PhongMaterial.hpp"

class Hit {
public:
  virtual ~Hit();
  Hit();
  glm::vec3 Reflection(glm::vec3 V);
  void copy(Hit hit0);

  glm::vec3 pos;
  glm::vec3 normal;
  float t=0;
  float U;
  float V;
  glm::vec3 Pu;
  glm::vec3 Pv;  
  PhongMaterial mat = PhongMaterial(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),0.0f);
};
