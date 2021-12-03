#include "Image.hpp"
#include <iostream>

class Texture {
public:
  virtual ~Texture();
  Texture( const std::string& fname );
  Texture();
  void LoadImage();
  Image image;

private:
  std::string m_fname;

};
