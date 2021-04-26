#pragma once
#include <vector>
#include <map>
#include <memory>


namespace RenderEngine
{
    class ShaderProgramm;
    class Texture2D;
    class Sprite;
    class AnimateSprite;
}
class Menu;

class Builder{
    public:
    virtual ~Builder(){}
    virtual void ProducePartA() const =0;
    virtual void ProducePartB() const =0;
    virtual void ProducePartC() const =0;
};


class Text2Dbuild:Builder{
public:
    Text2Dbuild(){this->Reset();}
    void Reset();
private:
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> Texture2DMap;
    Texture2DMap _texture2D;
    
};
