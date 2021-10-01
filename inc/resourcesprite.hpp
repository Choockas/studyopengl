#pragma once
#include "resourceaccess.hpp"
#include "document.h"
#include "error/en.h"
#include <memory>
#include <vector>
#include <map>


//there are class for working with any sprites

class ResourceSprite:public ResourceAcces
{
public:
    ResourceSprite(const std::string path, const std::string resourcePath);
    virtual ~ResourceSprite();
  
    bool loadJsonResources() override;

struct ThreeStringsDate
{
    std::string texture;
    std::string shader;
    std::string initial;
};

    bool get_spriteDate(const std::string spriteName, std::string& shaderName, std::string& textureName, std::string& initialTextName);
    const std::pair<std::string, std::string>  get_shaderDate(const std::string shaderProgName);
    const std::pair<std::string, std::string>  get_textureDate(const std::string textureName);
    const std::vector<std::string> get_subTextures(const std::string texturesName);
    bool get_aniDate(const std::string spriteName,std::map<std::string,std::vector<std::pair<std::string,uint64_t>>>& anidate);
    
private:
    
    std::map<const std::string ,std::pair<std::string, std::string> > _shadersDate;
    std::map<const std::string,std::pair<std::string,std::string>> _textureDate;
    std::map<const std::string,std::pair<unsigned int,unsigned int>> _subTextSizes;
    std::map<const std::string,std::vector<std::string>> _subTextures;
    typedef std::map<const std::string,ThreeStringsDate> spriteDate;
    spriteDate _spriteDate; 
    typedef std::map<std::string,std::map<std::string,std::vector<std::pair<std::string,uint64_t>>>> aniDate;
    aniDate _aniDate;
    rapidjson::Document _document;
    std::string _resourcePath;
    
public:
    
    
};


