#include "menu.hpp"
#include "igraphicobject.hpp"
#include <memory>
#include "resourcemanager.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shaderprogramm.hpp"

const unsigned int PADLENGTH =43;
const unsigned int PADHIGTH = 16;


Menu::Menu(const std::string relativepath, const std::string workpath, const float swidth, const float shight):_width(swidth),_hight(shight) 
{
    _rm = std::make_shared<ResourceManager>(workpath,relativepath);
    _rm->loadJsonResources();
    const std::vector<MenuPoint> rowMenu =_rm->get_menu();
    std::vector<MenuPoint> _rowMenu2 =_rm->get_menu();
    
    if (rowMenu.empty()){
        std::cerr<<"Empty menu";
    }
    
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

void Menu::initMenu()
{
    //     auto pSpriteShaderProgram = _rm->getShaderProgram("spriteShader");
   auto pSpriteShaderProgram = _rm->getShaderProgram("spriteShader");
    
    if (!pSpriteShaderProgram){
        std::cerr<<"Can't find shader programm " << "spriteShader" <<std::endl;
    }
    
    glm::mat4 projectionMatrix = glm::ortho (0.0f, static_cast<float>(_width),0.0f,static_cast<float>(_hight),-0.1f,100.0f);
    pSpriteShaderProgram->use(); 
    pSpriteShaderProgram->setInt("tex",0);
    pSpriteShaderProgram -> setMatrix4("projectionMat", projectionMatrix);
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


// manipulation with menupads
void Menu::update(const uint64_t delta)
{
    std::string  temp_actlabel, temp_label;
    
    glm::vec2 temp_position={0.f,0.f};
    for (const auto& currentMapObject : _vecObjects)
    {
        // checking only visible objects   
        if (currentMapObject->get_visible())
        {
            //first getting idAct trough checking position of mouse    
            currentMapObject->update(delta); //now turn to invisible
            //if matching up (by status dirty  get position (and label)
            if(currentMapObject->get_dirty())
            {  
                temp_position = currentMapObject->get_position();
                temp_actlabel = currentMapObject->get_label();                                
            }
        }
    }
    
    // look up by label  to make change in visibility and pass position
    for (const auto& currentMapObject : _vecObjects)
    {
        temp_label= currentMapObject->get_label();        
        if ((temp_label==temp_actlabel) || (temp_label== temp_actlabel+"_check")||(temp_actlabel==temp_label+"_check") ){
            currentMapObject->switch_visible();
            currentMapObject->set_position(temp_position); 
            //flash status dirty or change actually menu status 
            currentMapObject->get_dirty()?currentMapObject->set_dirty(): set_actualy(currentMapObject->get_idAct());
        }            
    }     
}

//getting a sprite for menues point
std::shared_ptr< ItemPad > Menu::createGOmenuPoint(const std::string label, glm::vec2 position, const glm::vec2 size, const float rotation, const bool visible, uint idAct)
{
    return std::make_shared<ItemPad>(_rm->getSprites(label),position,size,rotation,label,visible,idAct);  
}

 
