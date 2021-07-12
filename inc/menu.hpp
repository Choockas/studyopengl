#pragma once
#include <string>
#include <vector>
#include "itempad.hpp"
#include <map>
// #include "GLFW/glfw3.h"
// #include "shaderprogramm.hpp"


// class IGraphicObject;
class ResourceMenu;


class Menu
{
public:
    Menu(const std::string relativepath, const std::string workpath,const int swidth,const int shight);
    std::shared_ptr<ItemPad>createGOmenuPoint(const std::string label, 
                                              glm::vec2 position, 
                                              const glm::vec2 size, 
                                              const float rotation, 
                                              const bool visible, 
                                              std::shared_ptr< std::map<const int, const std::string>> vacts); 
    ~Menu();
    void render() const;
    void update(const uint factorSize);
    void set_actbyMenu(unsigned int ac_idAct);
    void clear_vecobjects(){_vecObjects.clear();}
    unsigned int get_actbyMenu(){return _actbyMenu;}
    void initMenu();
private:
    
    std::shared_ptr<ResourceMenu>   _resourseMenu; //recieve pointer to resources
    const int _width;
    const int  _hight;
    unsigned int _actbyMenu;
    std::vector <std::shared_ptr<ItemPad>> _vecObjects;
};
