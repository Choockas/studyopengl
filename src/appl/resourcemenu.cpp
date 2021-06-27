#include "resourcemenu.hpp"
#include "renderer.hpp"
#include "texture2D.hpp"
#include "sprite.hpp"
#include "itempad.hpp"
#include "framedsprite.hpp"
// #include <fstream>
// #include <sstream>
#include <memory>
// #define STB_IMAGE_IMPLEMENTATION
// #define STBI_ONLY_PNG
#include "stb_image.h"




ResourceMenu::ResourceMenu(const std::string path,const std::string resourcePath):_resourcePath(resourcePath)
{
    set_path(path);
    std::cout<<"Resource menu created"<<" ("<<_resourcePath<<") "<<std::endl;
}

ResourceMenu::~ResourceMenu()
{
    std::cout <<"Release resourse menu" << _resourcePath << std::endl;
}


bool ResourceMenu::loadJsonResources() 
{
    
    const std::string JSONstring = getFileString(_resourcePath);
    
    if (JSONstring.empty())
    {
        std::cerr << "No JSON resourses file"<< _resourcePath<<std::endl;
        return false;
    }
    
//read from json's file in the formatted string      
    rapidjson::Document document;
    rapidjson::ParseResult parsOk = document.Parse(JSONstring.c_str());
    if(!parsOk){
        std::cerr << "Parse file error "<< rapidjson::GetParseError_En(parsOk.Code())<<"("<<parsOk.Offset()<<")" <<std::endl;
        std::cerr << "In JSONfile:" << JSONstring<<std::endl;
        return false;
    }

    
       auto shadersIt = document.FindMember("shaders");
    if (shadersIt!=document.MemberEnd())
    {
        for (const auto& currentShader : shadersIt-> value.GetArray())
        {
            const std::string name = currentShader["name"].GetString() ;
            const std::string filepath_v = currentShader["filePath_v"].GetString() ;
            const std::string filepath_f = currentShader["filePath_f"].GetString() ;
            loadShaders(name, filepath_v,filepath_f);            
        }
    }
    
    auto textureAtlas = document.FindMember("textureAtlass");
    
    if (textureAtlas!=document.MemberEnd())
    {      
        size_t arrs;
        for (const auto& currentTextureAtlas : textureAtlas-> value.GetArray())
        {
            const std::string name = currentTextureAtlas["name"].GetString() ;
            const std::string filepath = currentTextureAtlas["filePath"].GetString() ;
            const unsigned int subTextureWidth = currentTextureAtlas["subTextureWidth"].GetUint() ;
            const unsigned int subTextureHight = currentTextureAtlas["subTextureHeight"].GetUint() ;
            const auto subTexturesArray = currentTextureAtlas["subTextureArray"].GetArray();
            std::vector<std::string> subTextures;
            arrs=subTexturesArray.Size();
            std::cout << "Gona to be reserved " << arrs << " for subtextures"<<std::endl;
            subTextures.reserve(subTexturesArray.Size());
            for(const auto& currentSubtextures : subTexturesArray){
                subTextures.emplace_back(currentSubtextures.GetString()); 
                std::cout << "emplace "<< currentSubtextures.GetString() << std::endl;
            }            
            loadTextureAtlas(get_path(),name, filepath,std::move(subTextures), subTextureWidth,subTextureHight);            
        }
    } else std::cout << "Something with textureAtalass ?" << std::endl;
    
    auto framedSpritesIt = document.FindMember("framedSprites");
    if (framedSpritesIt!=document.MemberEnd())
    {
        for (const auto& currentFramedSprite : framedSpritesIt-> value.GetArray())
        {
            const std::string name = currentFramedSprite["name"].GetString() ;
            const std::string atlas = currentFramedSprite["textureAtlas"].GetString() ;
            const std::string shader = currentFramedSprite["shader"].GetString() ;
            const std::string  initialSubTexture = currentFramedSprite["initialSubTexture"].GetString();                                           
            auto pFramedSprite = loadFramedSprites(name,atlas,shader,initialSubTexture);
            if(! pFramedSprite ){
                std::cerr << "Can't load framedsprite (initial) "<< initialSubTexture << std::endl;
                continue;
            }            
            const auto statesArray = currentFramedSprite["states"].GetArray();
            for(const auto& currentStateArray : statesArray){
                const std::string stateName = currentStateArray["statesName"].GetString();
                const std::string subTexture = currentStateArray["subTexture"].GetString();                
                pFramedSprite->insertState(std::move(stateName),std::move(subTexture));
            }
        }
    }
    
    auto spritesIt = document.FindMember("sprites");
    if (spritesIt!=document.MemberEnd())
    {
        for (const auto& currentSprite : spritesIt-> value.GetArray())
        {
            const std::string name = currentSprite["name"].GetString() ;
            const std::string atlas = currentSprite["textureAtlas"].GetString() ;
            const std::string shader = currentSprite["shader"].GetString() ;
            const std::string  initialSubTexture = currentSprite["initialSubTexture"].GetString();                                           
            auto pAnimatedSprite = loadSprites(name,atlas,shader,initialSubTexture);
            if(! pAnimatedSprite ){
                std::cerr << "Can't load sprite (initial) "<< initialSubTexture << std::endl;
                continue;
            }            
        }
    }
    
//     auto menuPads = document.FindMember("itempads");
//     if (menuPads!=document.MemberEnd())
//     {
//         for(const auto& curentPad : menuPads->value.GetArray())
//         {
//             const MenuPoint menupoint {curentPad["name"].GetString(),
//                                        curentPad["idAct"].GetUint(),
//                                        curentPad["visible"].GetBool()};          
//                 _menu_start.emplace_back(menupoint);                
//                         
//         }        
//     }  
//     

    
    return true;    
}

//***** S H A D E R  L O A D************************************

bool ResourceMenu::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
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

//***** A T L A S  L O A D************************************
std::shared_ptr< RenderEngine::Texture2D > ResourceMenu::loadTextureAtlas(const std::string& resourcePath,
                                                                             const std::string& textureName,
                                                                             const std::string& stexturePath,
                                                                             const std::vector<std::string> subTextures,
                                                                             const unsigned int subTexwidth,
                                                                             const unsigned int subTexheight)
{
    
/*
 * If u need many textures from one image this is used. Atlas of textures!
*/    
    auto pTexture = loadTextures(std::move(resourcePath), std:: move(textureName),std:: move(stexturePath));
    
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
std::shared_ptr<RenderEngine::Sprite> ResourceMenu::loadSprites(const std::string& spriteName,
                                                                   const std::string& textureName,
                                                                   const std::string& shaderName,
                                                                   const std::string& subtextureName )
{
    

    auto pTexture  = getTextures(textureName);
    if(!pTexture){
        std::cerr<< "Can't get textures "<< textureName<<" for the sprite:"<<spriteName<<std::endl;
        //glfwTerminate();
        return nullptr;
    }
    
    auto pShader = getShaderProgram(shaderName);
    if(!pShader){
        std::cerr<< "Can't get shader "<< shaderName<<" for the sprite:"<<spriteName<<std::endl;
        // glfwTerminate();
        return nullptr; 
        
    }

    std::shared_ptr<RenderEngine::Sprite> newSprite = _sprites.emplace(spriteName,
                                                                        std::make_shared<RenderEngine::Sprite>(pTexture,
                                                                                                               subtextureName,
                                                                                                               pShader)).first->second;
    std::cout<<"spriteName: "<< spriteName<< " loaded"<<std::endl;                                                                                                           
    return newSprite;
                                                                                                               
}

//***** T E X T U R E  L O A D************************************
std::shared_ptr<RenderEngine::Texture2D> ResourceMenu::loadTextures(const std::string& resourcePath, 
                                                                       const std::string& textureName, 
                                                                       const std::string& texturePath)
{
    int chanels = 0;
    int width = 0;
    int hight = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels =stbi_load(std::string(resourcePath+"/"+texturePath ).c_str(),&width,&hight,&chanels,0);
    std::cout<<"textureName: "<< textureName<<std::endl;
    if(!pixels){
        std::cerr<<"Can't load image "<<texturePath<<std::endl;
        return nullptr;
    }
    
    std::shared_ptr<RenderEngine::Texture2D>& newTexture =
    _texture2D.emplace(textureName,
                        std::make_shared<RenderEngine::Texture2D>(width,
                                                                  hight,
                                                                  pixels,
                                                                  chanels,
                                                                  GL_NEAREST,
                                                                  GL_CLAMP_TO_EDGE )).first->second;
                                                                  stbi_image_free(pixels);                                                               
    return newTexture;
}





//***** F R A M E D   S P R I T E  L O A D************************************
std::shared_ptr<RenderEngine::FramedSprite> ResourceMenu::loadFramedSprites(const std::string& spriteName, const std::string& textureName, const std::string& shaderName, const std::string& subtextureName)
{
        auto pTexture  = getTextures(textureName);
    if(!pTexture){
        std::cerr<< "Can't get textures "<<textureName <<" for the sprite:"<<spriteName<<std::endl;
        //glfwTerminate();
        return nullptr;
    }
    
    auto pShader = getShaderProgram(shaderName);
    if(!pShader){
        std::cerr<< "Can't get shader "<<shaderName<<"for the sprite:"<<spriteName<<std::endl;
        // glfwTerminate();
        return nullptr;
    }
    std::shared_ptr<RenderEngine::FramedSprite> newSprite = _framesprites.emplace(spriteName,
                                                                                  std::make_shared<RenderEngine::FramedSprite>(pTexture,
                                                                                                                                subtextureName,
                                                                                                                            pShader)).first->second;
    return newSprite;                                                                                                                                
}



//***** T E X T U R E  G E T************************************
std::shared_ptr<RenderEngine::Texture2D> ResourceMenu::getTextures(const std::string& textureName)
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
std::shared_ptr<RenderEngine::ShaderProgramm> ResourceMenu::getShaderProgram(const std::string& shaderName)
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

//***** S P R I T E  G E T************************************
std::shared_ptr<RenderEngine::Sprite> ResourceMenu::getSprites(const std::string& spriteName)
{
    SpriteMap::const_iterator it=_sprites.find(spriteName);
    if(it!=_sprites.end()){
        return it->second;
    }
    std::cerr<<"Can't find sprite"
    <<spriteName
    <<std::endl;
    return nullptr;
}

//***** F R A M E S P R I T E  G E T************************************
std::shared_ptr<RenderEngine::FramedSprite> ResourceMenu::getFramedSprites(const std::string& framespriteName)
{
    FrameSpriteMap::const_iterator it=_framesprites.find(framespriteName);
    if(it!=_framesprites.end()){
        return it->second;
    }
    std::cerr<<"Can't find sprite"
    <<framespriteName
    <<std::endl;
    return nullptr;
}



// void ResourceMenu::managerInit(const std::string& exepath)
// {
//     set_path(exepath);
//     loadJsonResources("res/startres.json");
//     
// }

// void ResourceDirector::jsonInvolver(std::string resourceJFileName)
// {
// 
//     loadJsonResources(resourceJFileName);
// }






