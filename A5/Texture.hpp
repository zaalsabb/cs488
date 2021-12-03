#pragma once
#include "Image.hpp"
#include <iostream>
#include <glm/glm.hpp>

class Texture {
public:
  virtual ~Texture();
  Texture( const std::string& fname );
  void loadTexture();
  glm::vec3 getColor(int x, int y);

  Image *image = new Image();
  std::string m_fname = "";  
};
