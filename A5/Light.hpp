#pragma once

#include <iosfwd>

#include <glm/glm.hpp>

// Represents a simple point light.
struct Light {
  Light();
  
  glm::vec3 colour;
  glm::vec3 position;
  float radius;
  int samples;
  double falloff[3];
};

std::ostream& operator<<(std::ostream& out, const Light& l);
