#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "glm/vec2.hpp"
// #include "GLFW/glfw3.h"
// #include "shaderprogramm.hpp"


// class IGraphicObject;
class ResourceMenu;
class ItemPad;

// class Menu  container for menupad as graphic object and menupoint as  
class Menu
{
public:
    Menu(const std::string relativepath, const std::string workpath,const int swidth,const int shight);
    std::shared_ptr<ItemPad>createGOmenuPoint(const std::string label, 
                                              glm::vec2 position, 
                                              const glm::vec2 size, 
                                              const float rotation, 
                                              const bool visible, 
                                              std::shared_ptr< std::array<std::pair<int,std::string>,2>> vacts); 
    ~Menu();
    void render() const;
    void update(const uint factorSize); //factorSize for actually positioning
    void clear_vecobjects(){_vecObjects.clear();} 
    unsigned int get_actbyMenu() const {return _actbyMenu;} //define the act that must be done
    void set_actbyMenu(const int res){_actbyMenu=res;}
    void initMenu();
private:
    
    std::shared_ptr<ResourceMenu>   _resourseMenu; //recieve pointer to resources
    const int _width;
    const int  _hight;
    unsigned int _actbyMenu;
    std::vector <std::shared_ptr<ItemPad>> _vecObjects; 
};
