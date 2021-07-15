#include "itempad.hpp"

#include "glm/vec2.hpp"
#include "framedsprite.hpp"
#include "mouse.hpp"




ItemPad::ItemPad(const std::shared_ptr< RenderEngine::FramedSprite > ptrSprite, 
                                                               const glm::vec2 position, 
                                                               const glm::vec2 size, 
                                                               const float rotation,
                                                               const std::string label,
                                                               const bool visible,
                                                               std::shared_ptr<std::array<std::pair<int,std::string>,2>>  vacts
                                                               )
                                                               :IGraphicObject(position,
                                                                               size,
                                                                               rotation,                                                        
                                                                               visible), 
                                                                _pEmbededSprite(ptrSprite),_label(label)
{
    std::cout << "emplace pad "<< label<<std::endl;
    _acts = vacts;

}

ItemPad::~ItemPad()
{
    std::cout<<"menuPad destructor"<<std::endl;
    _pEmbededSprite.use_count();
}


void ItemPad::render() const
{
    
     _pEmbededSprite->render(_position,_size,_rotation);
}

void ItemPad::update(const uint delta)
{
    _act_Off = !_act_Off; 
    _act_Off? _pEmbededSprite->update(_acts->at(1).second) :
              _pEmbededSprite->update(_acts->at(0).second) ;
   _dirty=false;
}


void ItemPad::check_dirty(uint fsize)
{
    const int xpos = MouseViewPort::get_xpos();
    const int ypos = MouseViewPort::get_ypos();
    const int mbut = MouseViewPort::get_button();
    //It just use mirroring ordinate and set dirty
    if((xpos>_position.x) && (xpos<_position.x+_size.x) && (fsize-ypos>_position.y)&&(fsize-ypos<_position.y+_size.y))
    {
       _dirty?_dirty=false:_dirty=true;
        
    }
    
    
}

int ItemPad::get_curentact()
{
    return  _act_Off? _acts->at(0).first : _acts->at(1).first;
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
