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
    bool tempChange=false;
    std::string  temp_actlabel;
    glm::vec2 temp_position={0.f,0.f};
    for (const auto& currentMapObject : _vecObjects)
    {
        
        if (currentMapObject->get_visible())
        {
            currentMapObject->update(delta);
            if (!currentMapObject->get_visible()){
                temp_position = currentMapObject->get_position();
                temp_actlabel = currentMapObject->get_label();
                tempChange=true;
                currentMapObject->switch_visible();
                set_dirty(currentMapObject->get_idAct());
            }
        }
    }
    if (tempChange)
    {
        std::string  temp_label;
        for (const auto& currentMapObject : _vecObjects)
        {
            temp_label= currentMapObject->get_label();
            
            if ((temp_label==temp_actlabel) || (temp_label== temp_actlabel+"_check")||(temp_actlabel==temp_label+"_check") ){
                currentMapObject->switch_visible();
                currentMapObject->set_position(temp_position);
                
            }            
        } 
    }
    std::cout<<"menu dirty: "<<get_dirty()<<std::endl;
    tempChange = false;
    temp_actlabel.erase();
}

std::shared_ptr< MenuPad > Menu::createGOmenuPoint(const std::string label, glm::vec2 position, const glm::vec2 size, const float rotation, const bool visible, uint idAct)
{
    return std::make_shared<MenuPad>(_rm->getSprites(label),position,size,rotation,label,visible,idAct);  
}

 
