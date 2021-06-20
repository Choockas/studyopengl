#pragma once
#include <string>
#include <vector>
// #include <memory>
#include "itempad.hpp"
#include "GLFW/glfw3.h"


// class IGraphicObject;
class ResourceManager;


class Menu
{
public:
    Menu(const std::string relativepath, const std::string workpath);
    std::shared_ptr<ItemPad>createGOmenuPoint(const std::string label, glm::vec2 position, const glm::vec2 size, const float rotation, const bool visible, uint idAct); 
    ~Menu();
    void render() const;
    void update(const uint64_t);
    void set_actualy(unsigned int ac_idAct){_actualy=ac_idAct;}
    void clear_vecobjects(){_vecObjects.clear();}
    unsigned int get_actualy(){return _actualy;}
private:
    
    std::shared_ptr<ResourceManager>   _rm; //recieve pointer to resources
    size_t _width;
    size_t  _hight;
    unsigned int _actualy;
    std::vector <std::shared_ptr<ItemPad>> _vecObjects;
};
