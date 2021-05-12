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
                                                                               visible), 
                                                                _pCurrentSprite(ptrSprite),  _idAct(idAct),_label(label)
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
    unsigned int ac_idAct;
    //
    if((xpos>_position.x) && (xpos<_position.x+_size.x) && (600-ypos>_position.y)&&(600-ypos<_position.y+_size.y))
    {

        ac_idAct = get_idAct();
        std::cout <<"label : "<< get_label()<<"  idAct : "<< ac_idAct<<std::endl;
        //just only to finding this point, actualy visibility take change in the menus rule
        switch_visible();
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
