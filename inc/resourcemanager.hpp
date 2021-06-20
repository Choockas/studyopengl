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
    class AnimateSprite;
}
class Menu;
class ResourceManager;

//this structure is container for json's file attribute
struct ResourceBit{
    std::string s_name;
    std::string s_path;
};

typedef struct {
    std::string name;
    uint idAct;
    bool visible;
    
} MenuPoint;


class ResourceManager:public ResourceAcces
{
public:
    ResourceManager(std::string path,std::string resource_path );
    virtual ~ResourceManager();
//     void managerInit(const std::string& exepath){};    
    bool loadJsonResources() override;
    std::shared_ptr<RenderEngine::Texture2D> getTextures(const std::string& textureName);
    std::shared_ptr<RenderEngine::Sprite> getSprites(const std::string& spriteName);
    std::shared_ptr<RenderEngine::ShaderProgramm> getShaderProgram(const std::string& shaderName);
    std::shared_ptr<RenderEngine::AnimateSprite> getAnimateSprites(const std::string& spriteName);
    
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
    std::shared_ptr<RenderEngine::AnimateSprite> loadAnimateSprites(const std::string& spriteName,
                                                                         const std::string& textureName,
                                                                         const std::string& shaderName,
                                                                         const std::string& subtextureName = "default");
    
    std::vector<MenuPoint> get_menu() const {return _menu_start;}
          
protected:
    
    
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgramm>> ShaderProgramsMap;
    ShaderProgramsMap _shaderPrograms;
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> Texture2DMap;
    Texture2DMap _texture2D;    
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpriteMap;
    SpriteMap _sprites;
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::AnimateSprite>> AniSpriteMap;
    AniSpriteMap _anisprites;
    std::vector<MenuPoint> _menu_start;
    
private:
    
    rapidjson::Document _document;
    std::string _resourcePath;
    
};

/*
class ResourceBuilder
{
public:
    ResourceBuilder();
    virtual ~ResourceBuilder();
    virtual bool loadShaders(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath )=0;
    virtual std::string getFileString(const std::string& relativePath)=0;
    virtual std::string get_path()const =0;
    virtual void set_path(std::string path)=0;
    virtual std::shared_ptr<RenderEngine::Texture2D> loadTextures(const std::string& resourcePath,
                                                          const std::string& textureName,
                                                          const std::string& texturePath )=0;
    virtual std::shared_ptr<RenderEngine::ShaderProgramm> getShaderProgram(const std::string& shaderName)=0;
    virtual std::shared_ptr<RenderEngine::Texture2D> getTextures(const std::string& textureName)=0;
    
    
};
*/
