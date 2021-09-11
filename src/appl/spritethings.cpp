#include "renderer.hpp"
#include "spritethings.hpp"
#include "texture2D.hpp"
#include "sprite.hpp"
#include "animatesprite.hpp"
#include <string>
#include "memory"
#ifndef STB_IMAGE_IMPLEMENTATION
// #define STB_IMAGE_IMPLEMENTATION
// #define STBI_ONLY_PNG
# define ONE 1
#endif
#include "stb_image.h"


SpriteThings::SpriteThings(const std::string path,const std::string resource_path ):ResourceAcces(path), _resourcePath(resource_path)
{

}

SpriteThings::~SpriteThings()
{
    std::cout<<"spritething destroyed"<<std::endl;
}

bool SpriteThings::loadJsonResources()
{
    return true;
}



//***** S H A D E R  L O A D************************************
bool SpriteThings::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
        std::string vertexString = getFileString(vertexPath);
    if (vertexString.empty()){
        std::cerr<<"No vertex shader!"<< std::endl;
    }
    std::string fragmentString = getFileString(fragmentPath);
    if (fragmentString.empty()){
        std::cerr<<"No fragment shader!"<< std::endl;
    }
    
    std::shared_ptr<RenderEngine::ShaderProgramm>& newShader = _shaderPrograms.emplace(shaderName, std::make_shared<RenderEngine::ShaderProgramm>(vertexString,fragmentString)).first->second;
    if (!newShader->isCompiled()){
        std::cerr<< "Can't load shader program:"<<"\n"
        <<"Vertex: " << vertexPath<< "\n" 
        <<"Fragment: " <<fragmentPath
        <<std::endl;
        return false;
    }
    std::cout<<"shader programm " <<shaderName << " loaded right"<<std::endl;
    return true;
}

//**************** T E X T U R E   L O A D *************
// std::shared_ptr<RenderEngine::Texture2D> SpriteThings::loadTextures(const std::string& resourcePath, const std::string& textureName, const std::string& texturePath)
bool SpriteThings::loadTextures(const std::string& resourcePath, const std::string& textureName, const std::string& texturePath)
{
       int chanels = 0;
    int width = 0;
    int height = 0;
    int chko = ONE;
    
    stbi_set_flip_vertically_on_load(true);
    const std::string imgpath = resourcePath+"/"+ texturePath;
    unsigned char* pixels =stbi_load(imgpath.c_str(),&width,&height,&chanels,0);
    std::cout<<"textureName: "<< textureName<< " loaded"<<std::endl;
    if(!pixels){
        std::cerr<<"Can't load image "<<texturePath<<std::endl;
        return false;
    }
    glm::vec2 leftBottomUV( 0.f, 0.f);
//       glm::vec2 rightTopUV(static_cast<float>(textureWidth),static_cast<float>(textureHeigth) );
    glm::vec2 rightTopUV(1.f,1.f );
    std::shared_ptr <RenderEngine::Texture2D> neustexture  = std::make_shared<RenderEngine::Texture2D>(width,
                                                                                                      height,
                                                                                                      pixels,
                                                                                                      chanels, 
                                                                                                      GL_NEAREST,
                                                                                                      GL_CLAMP_TO_EDGE);
    neustexture->addSubTextures2D(textureName,leftBottomUV,rightTopUV);
    
    std::shared_ptr<RenderEngine::Texture2D>& newTexture =  _texture2D.emplace(textureName,move(neustexture)).first->second;
    stbi_image_free(pixels);  
    if(newTexture){

      return true;     
    }                                                              
    
    else {
        std::cerr<< "texture "<< textureName << " lost ! "<<std::endl;
        return false;
    }
}


//***** T E X T U R E  A T L A S  L O A D************************************
std::shared_ptr< RenderEngine::Texture2D > SpriteThings::loadTextureAtlas(const std::string& resourcePath,
                                                                             const std::string& textureName,
                                                                             const std::string& stexturePath,
                                                                             const std::vector<std::string> subTextures,
                                                                             const unsigned int subTexwidth,
                                                                             const unsigned int subTexheight)
{
    
/*
 * If u need many textures from one image this is used. Atlas of textures!
*/    
    
//     auto pTexture = loadTextures(std::move(resourcePath), std:: move(textureName),std:: move(stexturePath));
    auto pTexture = getTextures(textureName);
    
    if (pTexture) {
        const unsigned int textureWidth = pTexture ->getWidth();
        const unsigned int textureHigth = pTexture ->getHight();
        unsigned int currentTextureOffsetX = 0;
        unsigned int currentTextureOffsetY = textureHigth;
        for (const auto& currentSubtextureName:subTextures)
        {
            glm::vec2 leftBottomUV(static_cast<float> (currentTextureOffsetX +0.01f)/textureWidth, static_cast<float>(currentTextureOffsetY-subTexheight+0.01f)/textureHigth );
            glm::vec2 rightTopUV(static_cast<float> (currentTextureOffsetX+subTexwidth-0.01f)/textureWidth, static_cast<float>(currentTextureOffsetY-0.01f)/textureHigth );
            pTexture->addSubTextures2D(std::move(currentSubtextureName),leftBottomUV,rightTopUV);
            currentTextureOffsetX+=subTexwidth;
            if (currentTextureOffsetX>=textureWidth)
            {
                currentTextureOffsetX = 0;
                currentTextureOffsetY -= subTexheight;
            }
        }
        
    }
    
    return pTexture; 
}


//***** S P R I T E  L O A D************************************
std::shared_ptr<RenderEngine::Sprite> SpriteThings::loadSprites(const std::string& spriteName, const std::string& textureAtlas, const std::string& shaderName, const std::string& subtextureName)
{
      std::cout<<"Start loading sprite, texturename: "<<textureAtlas <<"\t subtexturename: "<<subtextureName<<std::endl; 
    //auto pTexture  = getTextures(subtextureName); //getting texture from map
    auto pTexture  = getTextures(textureAtlas);
    if(!pTexture){
//         std::cerr<< "Can't get textures "<< subtextureName<<" for the sprite:"<<spriteName<<std::endl;
        std::cerr<< "Can't get textures "<< textureAtlas<<" for the sprite:"<<spriteName<<std::endl;
        return nullptr;
    }
    
    auto pShader = getShaderProgram(shaderName);//getting shader from map
    if(!pShader){
        std::cerr<< "Can't get shader "<< shaderName<<" for the sprite:"<<spriteName<<std::endl;
      
        return nullptr; 
        
    }

    std::shared_ptr<RenderEngine::Sprite> newSprite = _sprites.emplace(spriteName,
                                                                        std::make_shared<RenderEngine::Sprite>(pTexture,
                                                                                                               subtextureName,
                                                                                                               pShader)).first->second;
    std::cout<<"spriteName: "<< spriteName<< " loaded"<<std::endl;  
    return newSprite;
}



//***** A N I M A T E D   S P R I T E  L O A D************************************
bool SpriteThings::loadAnimateSprites(const std::string& spriteName, 
                                      const std::string& textureName, 
                                      const std::string& shaderName, 
                                      const std::string& subtextureName,
                                      const std::string& state, 
                            const std::vector<std::pair<std::string, uint64_t > > subTexturesDuration)
{
    bool result=false;
    
        auto pTexture  = getTextures(textureName);
    if(!pTexture){
        std::cerr<< "Can't get textures "<<textureName <<" for the sprite:"<<spriteName<<std::endl;
        
        return false;
    }
    
    auto pShader = getShaderProgram(shaderName);
    if(!pShader){
        std::cerr<< "Can't get shader "<<shaderName<<"for the sprite:"<<spriteName<<std::endl;
        
        return false;
    }
    std::shared_ptr<RenderEngine::AnimateSprite> newSprite = m_anisprites.emplace(spriteName,
                                                                                  std::make_shared<RenderEngine::AnimateSprite>(pTexture,
                                                                                                                                subtextureName,
                                                                                                                                 pShader)).first->second;
  newSprite->insertState(state, subTexturesDuration);  
  std::string newstate = "fly_rigth";  
  newSprite->setState(newstate);
  newSprite->render({200,300},{128,128},0);
// std::shared_ptr<RenderEngine::AnimateSprite> newSprite = m_anisprites.emplace(spriteName, _sprites.find(spriteName)
if(newSprite!=nullptr)result = true;                                                                                                                                 
// void AnimateSprite::insertState(std::string state, std::vector<std::pair<std::string, uint64_t > > subTexturesDuration)                                                                                                                                
//     newSprite->insertState();                                                                                                                                
    return result;                                                                                                                                
}






//***** T E X T U R E  G E T************************************
std::shared_ptr<RenderEngine::Texture2D> SpriteThings::getTextures(const std::string& textureName)
{

    Texture2DMap::const_iterator it=_texture2D.find(textureName);
    if(it!=_texture2D.end()){
        return it->second;
    }
    std::cerr<<"Can't find texture "
    <<textureName
    <<std::endl;
    return nullptr;
}

//***** S H A D E R  G E T************************************
std::shared_ptr<RenderEngine::ShaderProgramm> SpriteThings::getShaderProgram(const std::string& shaderName)
{
    ShaderProgramsMap::const_iterator it=_shaderPrograms.find(shaderName);
    if(it!=_shaderPrograms.end()){
        return it->second;
    }
    std::cerr<<"Can't find the shader program "
    <<shaderName
    <<std::endl;
    return nullptr;
}

//***** S P R I T E  G E T ************************************
std::shared_ptr<RenderEngine::Sprite> SpriteThings::getSprites(const std::string& spriteName)
{
    SpriteMap::const_iterator it=_sprites.find(spriteName);
    if(it!=_sprites.end()){
        return it->second;
    }
    std::cerr<<"Can't find sprite"<<spriteName<<std::endl;
    return nullptr;
}

//***** A N I M A T E  S P R I T E  G E T ************************************

std::shared_ptr<RenderEngine::AnimateSprite> SpriteThings::getAnimateSprites(const std::string& spriteName)
{
    AniSpriteMap::const_iterator it = m_anisprites.find(spriteName);
    if(it!=m_anisprites.end()){        
        return it->second;
    }
    std::cerr<<"Can't find anisprite " <<spriteName <<std::endl;
    return nullptr;
    
}
/*
std::shared_ptr<RenderEngine::AnimateSprite> SpriteThings::loadAnimateSprites(const std::string& spriteName, const std::string& textureName, const std::string& shaderName,  const std::string& subtextureName,const unsigned int subTexwidth, const unsigned int subTexheight)
{
    auto pTexture  = getTextures(textureName);
    if(!pTexture){
        std::cerr<< "Can't get textures "<<"for the sprite:"<<spriteName<<std::endl;
        glfwTerminate();
        return nullptr;
    }
    
    auto pShader = getShaderProgram(shaderName);
    if(!pShader){
        std::cerr<< "Can't get shader "<<"for the sprite:"<<spriteName<<std::endl;
        glfwTerminate();
        return nullptr;
        
    }
    
    std::shared_ptr<RenderEngine::AnimateSprite> newSprite = m_anisprites.emplace(spriteName,
                                                                            std::make_shared<RenderEngine::AnimateSprite>(pTexture,
                                                                                                                        subtextureName,
                                                                                                                        pShader)).first->second;
    return newSprite;
                                                                                                                        
}
 */

