#include "menupad.hpp"

#include "glm/vec2.hpp"
#include "sprite.hpp"
#include "mouse.hpp"




MenuPad::MenuPad(const std::shared_ptr< RenderEngine::Sprite > ptrSprite, 
                                                               const glm::vec2 position, 
                                                               const glm::vec2 size, 
                                                               const float rotation,
                                                               const std::string label,
                                                               const bool visible,
                                                               uint idAct)
                                                               :IGraphicObject(position,
                                                                               size,
                                                                               rotation,
                                                                               label,
                                                                               visible), 
                                                                _pCurrentSprite(ptrSprite),  _idAct(idAct)
{
    std::cout << "emplace pad "<< label<<std::endl;
    
}

MenuPad::~MenuPad()
{
    std::cout<<"menuPad destructor"<<std::endl;
}


void MenuPad::render() const
{
    
    
     _pCurrentSprite->render(_position,_size,_rotation);
     
}

void MenuPad::update(uint64_t delta)
{
    const int xpos = MouseViewPort::get_xpos();
    const int ypos = MouseViewPort::get_ypos();
    const int mbut = MouseViewPort::get_button();
    //
    if((xpos>_position.x) && (xpos<_position.x+_size.x) && (600-ypos>_position.y)&&(600-ypos<_position.y+_size.y))
    {
//         std::cout<<"x="<<xpos<< "; y="<<ypos<<std::endl;
//         std::cout << "_position.x ="<<_position.x<<" size.x ="<<_size.x<<std::endl;
//         std::cout << "_position.y ="<<_position.y<<" size.y ="<<_size.y<<std::endl;
        
        std::cout <<"label : "<< get_label()<<"  idAct : "<< get_idAct()<<std::endl;
        set_visible(false);
//         MouseStatus::set_used(true);
    }
    
}

// bool MenuPad::mouseCollision(double xposition, double yposition) const
// {
//     int leftBorder = _position.x;
//     int rightBorder = _position.x+ _size.x;
//     int bottomBorder = _position.y;
//     int topBorder = _position.y+_size.y;
//     
//     if( xposition > leftBorder && xposition < rightBorder && yposition > bottomBorder && yposition < topBorder)
//         return true;
//     else return false;
// }
