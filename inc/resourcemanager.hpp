#pragma once
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "memory"
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

//this structure is container for json's file attribute
struct ResourceBit{
    std::string s_name;
    std::string s_path;
};

class ResourceManager{
public:
    ResourceManager();
    void managerInit(const std::string& exepath);    
    virtual bool loadJsonResources(const std::string& resourcePath );
    std::shared_ptr<RenderEngine::ShaderProgramm> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath );
    std::shared_ptr<RenderEngine::Sprite> getSprites(const std::string& spriteName);
    std::shared_ptr<RenderEngine::Texture2D> loadTextures(const std::string& textureName,const std::string& texturePath );
    std::map<const std::string, std::string> get_resourceMap() const { return _resourcesMap;}
protected:
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgramm>> ShaderProgramsMap;
    ShaderProgramsMap _shaderPrograms;
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> Texture2DMap;
    static Texture2DMap _texture2D;    
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpriteMap;
    static SpriteMap _sprites;
    
private:
    std::string getFileString(const std::string& relativePath);
    rapidjson::Document _document;
    std::vector<std::vector<std::string>> _vectorResourcesString;
    std::map<const std::string, std::string> _resourcesMap;
    
    
};

class Accesories:public ResourceManager 
{
public:
    Accesories();
    bool loadJsonResources(const std::string& resourcePath) override;
    
private:
    
};
/*
 
      
    
  
  
 */
