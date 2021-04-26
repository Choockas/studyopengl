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
    MenuPad(const std::shared_ptr< RenderEngine::Sprite > ptrSprite, 
                                          const glm::vec2 position, 
                                          const glm::vec2 size, 
                                          const float rotation,
                                          const std::string label, 
                                          const bool visible,
                                          uint idAct
           ); 
    ~MenuPad() override;
    void render() const override;
    void update(uint64_t delta) override;
    uint get_idAct()const {return _idAct;}
//     bool mouseCollision(double xposition, double yposition) const;
private:
    std::shared_ptr<RenderEngine::Sprite> _pCurrentSprite;
    bool _dirty = false;
    uint _idAct;
};
