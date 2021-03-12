#pragma once
#include "glm/vec2.hpp"

class IGraphicObject{
public:
IGraphicObject(const glm::vec2 position, const glm::vec2 size, const float rotation);
    virtual void render() const = 0;
    virtual void update(const uint64_t delta) = 0;
    virtual ~IGraphicObject();
protected:
    glm::vec2 _position;
    glm::vec2 _size;
    float _rotation;
    
};
