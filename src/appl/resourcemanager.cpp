#include "resourcemanager.hpp"
#include "renderer.hpp"
#include "texture2D.hpp"
#include "sprite.hpp"
#include "itempad.hpp"
#include "animatesprite.hpp"
#include <fstream>
#include <sstream>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"


ResourceAcces::~ResourceAcces()
{
}

ResourceAcces::ResourceAcces()
{
}


ResourceManager::ResourceManager():ResourceAcces()
{
    std::cout<<"resource m created"<<std::endl;
}

ResourceManager::~ResourceManager()
{
    
}



std::string ResourceAcces::getFileString(const std::string& relativePath)
{
    std::ifstream f;
    f.open(get_path()+"/"+relativePath,std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cerr<<"Failed to open "<< relativePath<<std::endl;
        return std::string();
    }
    std::stringstream buffer;
    buffer<<f.rdbuf();
    std::cout<< "getting string from "<< relativePath<<std::endl;
    return buffer.str();
}

bool ResourceSupport::loadJsonResources(const std::string& resourcePath)
{
    const std::string JSONstring = getFileString(resourcePath);
    
    if (JSONstring.empty())
    {
        std::cerr << "No JSON resourses file"<< resourcePath<<std::endl;
        return false;
    }
    rapidjson::Document document;
    rapidjson::ParseResult parsOk = document.Parse(JSONstring.c_str());
    if(!parsOk){
        std::cerr << "Parse file error "<< rapidjson::GetParseError_En(parsOk.Code())<<"("<<parsOk.Offset()<<")" <<std::endl;
        std::cerr << "In JSONfile:" << JSONstring<<std::endl;
        return false;
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
//             loadTextureAtlas(get_path(),name, filepath,std::move(subTextures), subTextureWidth,subTextureHight);            
        }
    } else std::cout << "Something with textureAtalass ?" << std::endl;
    return true;
    
}


bool ResourceManager::loadJsonResources(const std::string& resourcePath) 
{
    
    const std::string JSONstring = getFileString(resourcePath);
    
    if (JSONstring.empty())
    {
        std::cerr << "No JSON resourses file"<< resourcePath<<std::endl;
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
    
     auto resourceIt = document.FindMember("inits");
    
    if (resourceIt!=document.MemberEnd())
    {
        for (const auto& currentShader : resourceIt-> value.GetArray())
        {
            const std::string name = currentShader["name"].GetString() ;
            const std::string filepath_j = currentShader["path"].GetString() ;            
            _resourcesMap.emplace(name,filepath_j);
        }
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
    
    auto animateSpritesIt = document.FindMember("animatedSprites");
    if (animateSpritesIt!=document.MemberEnd())
    {
        for (const auto& currentAnimateSprite : animateSpritesIt-> value.GetArray())
        {
            const std::string name = currentAnimateSprite["name"].GetString() ;
            const std::string atlas = currentAnimateSprite["textureAtlas"].GetString() ;
            const std::string shader = currentAnimateSprite["shader"].GetString() ;
            const std::string  initialSubTexture = currentAnimateSprite["initialSubTexture"].GetString();                                           
            auto pAnimatedSprite = loadAnimateSprites(name,atlas,shader,initialSubTexture);
            if(! pAnimatedSprite ){
                std::cerr << "Can't load animatesprite (initial) "<< initialSubTexture << std::endl;
                continue;
            }            
            const auto statesArray = currentAnimateSprite["states"].GetArray();
            for(const auto& currentStateArray : statesArray){
                const std::string stateName = currentStateArray["statesName"].GetString();
                std::vector<std::pair<std::string,uint64_t>>  frames;
                const auto framesArray =  currentStateArray["frames"].GetArray();
                frames.reserve(framesArray.Size());
                for(const auto& currentFrame : framesArray){
                    const std::string subTexture = currentFrame["subTexture"].GetString();
                    const uint64_t duration = currentFrame["duration"].GetUint64();
                    frames.emplace_back(std::pair<std::string,uint64_t>(subTexture,duration));                    
                }
                pAnimatedSprite->insertState(stateName, std::move(frames));
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
    
    auto menuPads = document.FindMember("itempads");
    if (menuPads!=document.MemberEnd())
    {
        for(const auto& curentPad : menuPads->value.GetArray())
        {
            const MenuPoint menupoint {curentPad["name"].GetString(),
                                       curentPad["idAct"].GetUint(),
                                       curentPad["visible"].GetBool()};          
                _menu_start.emplace_back(menupoint);                
                        
        }        
    }  
    

    
    return true;    
}

//***** S H A D E R  L O A D************************************
std::shared_ptr<RenderEngine::ShaderProgramm> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
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
        return nullptr;
    }
    std::cout<<"shader programm " <<shaderName << " loaded right"<<std::endl;
    return newShader;
}

//***** A T L A S  L O A D************************************
std::shared_ptr< RenderEngine::Texture2D > ResourceManager::loadTextureAtlas(const std::string& resourcePath,
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
std::shared_ptr<RenderEngine::Sprite> ResourceManager::loadSprites(const std::string& spriteName,
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
std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTextures(const std::string& resourcePath, 
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





//***** A N I M A T E D   S P R I T E  L O A D************************************
std::shared_ptr<RenderEngine::AnimateSprite> ResourceManager::loadAnimateSprites(const std::string& spriteName, const std::string& textureName, const std::string& shaderName, const std::string& subtextureName)
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
    std::shared_ptr<RenderEngine::AnimateSprite> newSprite = _anisprites.emplace(spriteName,
                                                                                  std::make_shared<RenderEngine::AnimateSprite>(pTexture,
                                                                                                                                subtextureName,
                                                                                                                                pShader)).first->second;
    return newSprite;                                                                                                                                
}



//***** T E X T U R E  G E T************************************
std::shared_ptr<RenderEngine::Texture2D> ResourceManager::getTextures(const std::string& textureName)
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
std::shared_ptr<RenderEngine::ShaderProgramm> ResourceManager::getShaderProgram(const std::string& shaderName)
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
std::shared_ptr<RenderEngine::Sprite> ResourceManager::getSprites(const std::string& spriteName)
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



void ResourceManager::managerInit(const std::string& exepath)
{
    set_path(exepath);
    loadJsonResources("res/startres.json");
    
}

void ResourceAcces::supportInit(std::string resourceJFileName)
{
    loadJsonResources(resourceJFileName);
}






