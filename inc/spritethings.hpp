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



class SpriteThings:public ResourceAcces 
{
public:
    SpriteThings(const std::string path,const std::string resource_path );
    virtual ~SpriteThings();
    bool loadJsonResources() override;
    std::shared_ptr<RenderEngine::Texture2D> getTextures(const std::string& textureName);
    
    std::shared_ptr<RenderEngine::ShaderProgramm> getShaderProgram(const std::string& shaderName);
    bool loadShaders(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath );   
    bool loadTextures ( const std::string& resourcePath,const std::string& textureName, const std::string& texturePath);
    std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(
                                                              const std::string& textureName,
                                                              
                                                              const std::vector<std::string> subTextures,
                                                              const unsigned int subTexwidth,
                                                              const unsigned int subTexheight);
    std::shared_ptr<RenderEngine::Sprite> loadSprites(const std::string& spriteName,
                                                           const std::string& textureAtlas,
                                                           const std::string& shaderName,
                                                           const std::string& subtextureName = "default");
    
    //void AnimateSprite::insertState(std::string state, std::vector<std::pair<std::string, uint64_t > > subTexturesDuration)
    bool loadAnimateSprites(const std::string& spriteName, 
                            const std::string& textureName, 
                            const std::string& shaderName, 
                            const std::string& subtextureName
                           ,std::map<std::string,std::vector<std::pair<std::string,uint64_t >>> anidate);
/*                            
                            ,const std::string& state = "default", 
                            const std::vector<std::pair<std::string, uint64_t > > subTexturesDuration ={{"",0}} );
 */   
   std::shared_ptr<RenderEngine::Sprite> getSprites(const std::string spriteName);
   bool setCurrentAnimateSprites(const std::string spriteName); 
   void renderCurrentAnimationSprite(const glm::ivec2 position, const glm::ivec2 size, float rotation); 
   void updateCurrentAnimateSprite(uint64_t dur);
   
private:
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgramm>> ShaderProgramsMap;
    ShaderProgramsMap _mshaderPrograms;
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> Texture2DMap;
    Texture2DMap _mtexture2D;    
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpriteMap;
    SpriteMap _msprites;
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::AnimateSprite>> AniSpriteMap;
    AniSpriteMap _manisprites;
    std::string _resourcePath;
    std::shared_ptr<RenderEngine::AnimateSprite> _curentAnimateSprite;
};
