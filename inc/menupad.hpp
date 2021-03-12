#pragma once
#include "igraphicobject.hpp"
#include <memory>

namespace RenderEngine
{
    class Sprite;
}

class MenuPad : public IGraphicObject
{
public:
    MenuPad(const std::shared_ptr< RenderEngine::Sprite > ptrSprite, const glm::vec2 position, const glm::vec2 size, const float rotation); 
    ~MenuPad() override;
    virtual void render() const override;
    virtual void update(uint64_t delta) override;
private:
    std::shared_ptr<RenderEngine::Sprite> _pCurrentSprite;
};
