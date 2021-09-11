#pragma once
#include <iostream>
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


class ResourceAcces
{
public:
    ResourceAcces(const std::string workpath);
    virtual ~ResourceAcces();
    virtual bool loadJsonResources()=0;
    std::string getFileString(const std::string& relativePath);
    std::string get_execpath()const{return _path;}
//     void set_path(const std::string path){_path=path;};
    
private:;
  const std::string _path;
    
    
};


// class ResourceSprite:public ResourceAcces
class SpriteBuilder
{
public:
    SpriteBuilder(const std::string workpath);
    ~SpriteBuilder();
//     bool loadJsonResources() override {return true;};
//     std::shared_ptr<RenderEngine::Texture2D> getTextures(const std::string& textureName);
//     bool getTextures(const std::string& textureName);
//     std::shared_ptr<RenderEngine::Sprite> getSprites(const std::string& spriteName);
//     std::shared_ptr<RenderEngine::ShaderProgramm> getShaderProgram(const std::string& shaderName);
//     bool loadShaders(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath );
//     std::shared_ptr<RenderEngine::Texture2D> loadTextures(const std::string& resourcePath,
//                                                           const std::string& textureName,
//                                                           const std::string& texturePath );
//     std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(const std::string& resourcePath,
//                                                               const std::string& textureName,
//                                                               const std::string& stexturePath,
//                                                               const std::vector<std::string> subTextures,
//                                                               const unsigned int subTexwidth,
//                                                               const unsigned int subTexheight);
//     std::shared_ptr<RenderEngine::Sprite> loadSprites(const std::string& spriteName,
//                                                            const std::string& textureName,
//                                                            const std::string& shaderName,
//                                                            const std::string& subtextureName = "default");
private:
    const std::string  _workpath;
};
