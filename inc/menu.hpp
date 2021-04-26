#pragma once
#include <string>
#include <vector>
// #include <memory>
#include "menupad.hpp"
#include "GLFW/glfw3.h"


class IGraphicObject;
class ResourceManager;


class Menu
{
public:
    Menu(std::shared_ptr< ResourceManager > rm);
    std::shared_ptr<IGraphicObject>createGOmenuPoint(const std::string label, glm::vec2 position, const glm::vec2 size, const float rotation, const bool visible, uint idAct); 
    ~Menu();
    void render() const;
    void update(const uint64_t);
private:
    
     std::shared_ptr<ResourceManager>  _rm; //recieve pointer to resources
    size_t _width;
    size_t  _hight;
    std::vector <std::shared_ptr<IGraphicObject>> _vecObjects;
};
