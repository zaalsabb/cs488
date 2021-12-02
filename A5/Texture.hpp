#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

// A polygonal mesh.
class Texture : public Texture {
public:
  Texture( const std::string& fname );
  ~Texture();
  uint8_t* image;

};