#include "menu.hpp"
#include "igraphicobject.hpp"

#include "resourcemanager.hpp"


const unsigned int PADLENGTH =43;
const unsigned int PADHIGTH = 16;



Menu::Menu(std::shared_ptr<ResourceManager> rm) : _rm(rm)
{
        const std::vector<MenuPoint> rowMenu =_rm->get_menu();
    glm::ivec2 m_position{0,0};
    
    if (rowMenu.empty()){
        std::cerr<<"Empty menu";
    }
    
    
//     glGetIntegerv(GL_MAX_VIEWPORT_DIMS,&m_position);
    _vecObjects.reserve ( PADHIGTH * PADLENGTH*2);
    unsigned int  currentLeftOffset =0;
    
    for (MenuPoint currentPoint : rowMenu  )
    {
        
        _vecObjects.emplace_back( createGOmenuPoint(currentPoint.name, {currentLeftOffset,584},{PADLENGTH,PADHIGTH},0.f,currentPoint.visible,currentPoint.idAct));

        currentLeftOffset+=PADLENGTH;
    }
    
}


Menu::~Menu()
{
        
}


void Menu::render() const 
{
    
    for (const auto& currentMapObject : _vecObjects)
    {

        if (currentMapObject->get_visible())
        {
            
            currentMapObject->render();
        }
    }
    
}

void Menu::update(const uint64_t delta)
{
    for (const auto& currentMapObject : _vecObjects)
    {
     if (currentMapObject->get_visible())
        {
            currentMapObject->update(delta);
        }
    }
}

std::shared_ptr<IGraphicObject> Menu::createGOmenuPoint(const std::string label, 
                                                        const glm::vec2 position, 
                                                        const glm::vec2 size, 
                                                        const float rotation,
                                                        const bool visible,
                                                        const uint idAct
                                                       )
{
    return std::make_shared<MenuPad>(_rm->getSprites(label),position,size,rotation,label,visible,idAct);  
}

 
