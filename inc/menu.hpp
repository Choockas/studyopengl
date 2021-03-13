#pragma once
#include <string>
#include <vector>
#include <memory>
#include "menupad.hpp"



class IGraphicObject;

//std::shared_ptr<IGraphicObject>createGameObjectFromDescription(const char description,const glm::vec2 position, const glm::vec2 size, const float rotation)
//{
//     switch (description)
//     {
//         case '0':
//             return std::make_shared<MenuPad>(ResourceManager::getSprites("brickWall_Right"),position,size,rotation);  
//             break;
//         case '1':
//             
//             return std::make_shared<MenuPad>(ResourceManager::getSprites("brickWall_Bottom"),position,size,rotation);  
//             break;
//         case '3':
//             return std::make_shared<MenuPad>(ResourceManager::getSprites("brickWall_Left"),position,size,rotation);  
//             break;
//         case '4':
//             return std::make_shared<MenuPad>(ResourceManager::getSprites("brickWall_Top"),position,size,rotation);  
//             break;
//         default:
//             return std::make_shared<MenuPad>(ResourceManager::getSprites("nothing"),position,size,rotation);  
//             break;
//     }
    
//} 


class Menu
{
public:
    Menu(const std::vector< std::string>& menuDescription);
;
    void render() const;
    void update(const uint64_t);
private:
    size_t _width;
    size_t  _hight;
    std::vector <std::shared_ptr<IGraphicObject>> _mapOjects;
};
