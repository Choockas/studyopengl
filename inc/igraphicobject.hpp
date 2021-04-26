#pragma once
#include "glm/vec2.hpp"
#include <string>

class IGraphicObject{
public:
IGraphicObject(const glm::vec2 position, const glm::vec2 size, const float rotation, const std::string label, const bool visible);

    virtual void render() const = 0;
    virtual void update(const uint64_t delta) = 0;
    std::string get_label(); //{return _label;}
    void set_visible(bool state){_visible = state;}
    bool get_visible(){return _visible;}
    virtual ~IGraphicObject();
protected:
    glm::vec2 _position;
    glm::vec2 _size;
    float _rotation;
    std::string  _label;
    bool _visible;
    
};
