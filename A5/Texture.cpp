#include "Texture.hpp"


//---------------------------------------------------------------------------------------
Texture::Texture(const std::string& fname )
{
    // Load the texture
    int w, h, nch;
    image = stbi_load("image.png", &w, &h, &nch, 3);
}

//---------------------------------------------------------------------------------------
Texture::~Texture() {
    stbi_image_free(image);
}
