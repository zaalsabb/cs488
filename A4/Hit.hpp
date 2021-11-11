#pragma once

#include <glm/glm.hpp>

#include "PhongMaterial.hpp"

class Hit {
public:
  virtual ~Hit();
  Hit();
  glm::vec3 Reflection(glm::vec3 V);

  glm::vec3 pos;
  glm::vec3 n;
  float t=0;

  PhongMaterial mat = PhongMaterial(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),0.0f);
};
