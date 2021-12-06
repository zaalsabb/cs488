#pragma once
#include "Image.hpp"
#include "Perlin.hpp"
#include "Hit.hpp"

#include <iostream>
#include <glm/glm.hpp>
using namespace glm;

class Bump {
public:
  virtual ~Bump();
  Bump( const std::string& fname );
  Bump();
  void loadBump();
  float getDepth(int x, int y);
  vec2 gradient(int x, int y);
  void perturbNormal(int x, int y, Hit &hit);
  void perlinHeightMap();

  Image *image = new Image();
  std::string m_fname = "";

  float noise = 0.0f;
  int octave;
  int perlin_w;
  int perlin_h;
  Perlin perlin;

};
