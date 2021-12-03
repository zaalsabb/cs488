#include "Texture.hpp"


//---------------------------------------------------------------------------------------
Texture::Texture(const std::string& fname ) : m_fname(fname)
{
    // image.loadPng(fname);
}
//---------------------------------------------------------------------------------------
Texture::~Texture() {
}

void Texture::LoadImage(){
  image.loadPng(m_fname);
}
