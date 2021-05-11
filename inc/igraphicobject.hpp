#pragma once
#include "glm/vec2.hpp"
#include <string>

class IGraphicObject{
public:
IGraphicObject(const glm::vec2 position, const glm::vec2 size, const float rotation, const std::string label, const bool visible);

    virtual void render() const = 0;
    virtual void update(const uint64_t delta) = 0;
    std::string get_label(); //{return _label;}
    void switch_visible(){_visible = _visible ? false:true;}
    bool get_visible()const{return _visible;}
    glm::vec2 get_position()const {return _position;}
    void set_position(glm::vec2 newposition){ _position=newposition;}
    virtual ~IGraphicObject();
protected:
    glm::vec2 _position;
    glm::vec2 _size;
    float _rotation;
    std::string  _label;
    bool _visible;
    
};
