#include "igraphicobject.hpp"


/*
IGraphicObject::IGraphicObject(const glm::vec2 position, const glm::vec2 size, const float rotation, const std::string label)
                                : _position(position), _size(size), _rotation(rotation),_label(label)
   
{
    
    
}*/

IGraphicObject::IGraphicObject(const glm::vec2 position, const glm::vec2 size, const float rotation, const bool visible)
: _position(position), _size(size), _rotation(rotation), _visible(visible)
{
    
}





IGraphicObject::~IGraphicObject()
{
    
}
