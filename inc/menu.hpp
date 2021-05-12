#pragma once
#include <string>
#include <vector>
// #include <memory>
#include "menupad.hpp"
#include "GLFW/glfw3.h"


// class IGraphicObject;
class ResourceManager;


class Menu
{
public:
    Menu(std::shared_ptr< ResourceManager > rm);
    std::shared_ptr<MenuPad>createGOmenuPoint(const std::string label, glm::vec2 position, const glm::vec2 size, const float rotation, const bool visible, uint idAct); 
    ~Menu();
    void render() const;
    void update(const uint64_t);
    void set_dirty(unsigned int ac_idAct){_dirty=ac_idAct;}
    unsigned int get_dirty(){return _dirty;}
private:
    
    std::shared_ptr<ResourceManager>  _rm; //recieve pointer to resources
    size_t _width;
    size_t  _hight;
    unsigned int _dirty;
    std::vector <std::shared_ptr<MenuPad>> _vecObjects;
};
