#pragma once
#include "Image.hpp"
#include "Hit.hpp"

#include <iostream>
#include <glm/glm.hpp>
using namespace glm;

class Bump {
public:
  virtual ~Bump();
  Bump( const std::string& fname );
  void loadBump();
  float getDepth(int x, int y);
  vec2 gradient(int x, int y);
  void perturbNormal(int x, int y, Hit &hit);

  Image *image = new Image();
  std::string m_fname = "";
};
