#pragma once
#include "igraphicobject.hpp"
#include <memory>

namespace RenderEngine
{
    class Sprite;
}

class ItemPad : public IGraphicObject
{
public:
    ItemPad(const std::shared_ptr< RenderEngine::Sprite > ptrSprite, 
                                          const glm::vec2 position, 
                                          const glm::vec2 size, 
                                          const float rotation,
                                          const std::string label, 
                                          const bool visible,
                                          uint idAct
           ); 
    ~ItemPad() override;
    void render() const override;
    void update(uint64_t delta) override;
    uint get_idAct()const {return _idAct;}
    void set_dirty(){_dirty?_dirty=false:_dirty=true;};
    bool get_dirty(){return _dirty;}
    std::string get_label()const {return _label;}
//     bool mouseCollision(double xposition, double yposition) const;
private:
    std::shared_ptr<RenderEngine::Sprite> _pCurrentSprite;
    bool _dirty = false;
    uint _idAct;
    std::string _label;
};
