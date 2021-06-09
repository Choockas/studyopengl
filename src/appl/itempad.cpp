#include "itempad.hpp"

#include "glm/vec2.hpp"
#include "sprite.hpp"
#include "mouse.hpp"




ItemPad::ItemPad(const std::shared_ptr< RenderEngine::Sprite > ptrSprite, 
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

ItemPad::~ItemPad()
{
    std::cout<<"menuPad destructor"<<std::endl;
    _pCurrentSprite.use_count();
}


void ItemPad::render() const
{
    
    
     _pCurrentSprite->render(_position,_size,_rotation);
     
}

void ItemPad::update(uint64_t delta)
{
    const int xpos = MouseViewPort::get_xpos();
    const int ypos = MouseViewPort::get_ypos();
    const int mbut = MouseViewPort::get_button();
    //
    if((xpos>_position.x) && (xpos<_position.x+_size.x) && (600-ypos>_position.y)&&(600-ypos<_position.y+_size.y))
    {
        set_dirty();
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
