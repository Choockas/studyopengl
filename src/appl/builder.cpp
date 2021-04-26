#include "texture2D.hpp"
#include "builder.hpp"



void Text2Dbuild::Reset()
{
    this->_texture2D = *(new Texture2DMap);
}
