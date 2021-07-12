#pragma once
#include "igraphicobject.hpp"
#include <memory>
#include <vector>
#include <map>

namespace RenderEngine
{
    class FramedSprite;
}

class ItemPad : public IGraphicObject
{
public:
    ItemPad(const std::shared_ptr< RenderEngine::FramedSprite > ptrSprite, 
                                          const glm::vec2 position, 
                                          const glm::vec2 size, 
                                          const float rotation,
                                          const std::string label, 
                                          const bool visible, 
                                          std::shared_ptr<std::map<const int,const std::string>> vacts); 
    ~ItemPad() override;
    void render() const override;
    void update(const uint delta) override;
    void set_dirty(uint fsize);
//     std::shared_ptr<std::map<const int,const std::string>> get_acts() const { return _acts;}
    int get_act();
    
    bool get_dirty() const {return _dirty;}
    bool get_visible() const {return _visible;}
    int get_curentact() const {return _curentact;}
    std::string get_label()const {return _label;}

    
  
//     bool mouseCollision(double xposition, double yposition) const;
private:
    std::shared_ptr<RenderEngine::FramedSprite> _pEmbededSprite;
    bool _dirty = false;
    bool _visible;
    std::shared_ptr<std::map<const int,const std::string>>  _acts;
    int _nextact;
    int _curentact; 
    int _actSize;
    std::string _label;
};
