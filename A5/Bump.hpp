#pragma once
#include "Image.hpp"
#include <iostream>
#include <glm/glm.hpp>

class Bump {
public:
  virtual ~Bump();
  Bump( const std::string& fname );
  void loadBump();
  glm::vec3 getDepth(int x, int y);

  Image *image = new Image();
  std::string m_fname = "";
};
