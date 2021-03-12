#include "menupad.hpp"

#include "glm/vec2.hpp"
#include "sprite.hpp"


MenuPad::MenuPad(const std::shared_ptr< RenderEngine::Sprite > ptrSprite, const glm::vec2 position, const glm::vec2 size, const float rotation):IGraphicObject(position,size,rotation), _pCurrentSprite(ptrSprite)
{
    
}

MenuPad::~MenuPad()
{
    _pCurrentSprite.use_count();
}


void MenuPad::render() const
{
}

void MenuPad::update(uint64_t delta)
{
    
}
