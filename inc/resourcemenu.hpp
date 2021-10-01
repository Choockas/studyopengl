#pragma once
#include "resourceaccess.hpp"
#include "document.h"
#include "error/en.h"
#include <memory>
#include <vector>
#include <map>

namespace RenderEngine
{
    class ShaderProgramm;
    class Texture2D;
    class Sprite;
    class FramedSprite;
}

class Menu;

struct MenuPoint {
    const std::string tsprite;
    std::array<std::pair<int,std::string>,2> acts;
    const bool bvisible;
} ;

class ItemPad;

class ResourceMenu:public ResourceAcces
{
public:
    ResourceMenu(const std::string path, const std::string resourcePath);
    virtual ~ResourceMenu();   
    bool loadJsonResources() override;
    std::shared_ptr<RenderEngine::Texture2D> getTextures(const std::string& textureName);
    std::shared_ptr<RenderEngine::Sprite> getSprites(const std::string& spriteName);
    std::shared_ptr<RenderEngine::ShaderProgramm> getShaderProgram(const std::string& shaderName);
    std::shared_ptr<RenderEngine::FramedSprite> getFramedSprites(const std::string& framespriteName);
    
    bool loadShaders(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath );
    std::shared_ptr<RenderEngine::Texture2D> loadTextures(const std::string& resourcePath,
                                                          const std::string& textureName,
                                                          const std::string& texturePath );
    std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(const std::string& resourcePath,
                                                              const std::string& textureName,
                                                              const std::string& stexturePath,
                                                              const std::vector<std::string> subTextures,
                                                              const unsigned int subTexwidth,
                                                              const unsigned int subTexheight);
    std::shared_ptr<RenderEngine::Sprite> loadSprites(const std::string& spriteName,
                                                           const std::string& textureName,
                                                           const std::string& shaderName,
                                                           const std::string& subtextureName = "default");
    std::shared_ptr<RenderEngine::FramedSprite> loadFramedSprites(const std::string& spriteName,
                                                                         const std::string& textureName,
                                                                         const std::string& shaderName,
                                                                         const std::string& subtextureName = "default");
    
    std::vector<MenuPoint> get_menupoint() const {return _menuPoint;}
          
protected:
    
    
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgramm>> ShaderProgramsMap;
    ShaderProgramsMap _shaderPrograms;
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> Texture2DMap;
    Texture2DMap _texture2D;    
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpriteMap;
    SpriteMap _sprites;
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::FramedSprite>> FrameSpriteMap;
    FrameSpriteMap _framesprites;
    
    std::vector<MenuPoint> _menuPoint;
    
private:
    
    rapidjson::Document _document;
    std::string _resourcePath;
    
};


