#include "resourcesprite.hpp"
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"




ResourceSprite::ResourceSprite(const std::string path,const std::string resourcePath):ResourceAcces(path),_resourcePath(resourcePath)
{
    
    std::cout<<"resource m created"<<std::endl;
}

ResourceSprite::~ResourceSprite()
{
}

//parse from file  and write to memory
bool ResourceSprite::loadJsonResources() 
{
    const std::string JSONstring = getFileString(_resourcePath);
    const std::string workpath=get_execpath();
    
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
    
// ************** S H A D E R *********************
    auto shadersIt = document.FindMember("shaders");
    if (shadersIt!=document.MemberEnd())
    {
        for (const auto& currentShader : shadersIt-> value.GetArray())
        {
            const std::string name = currentShader["name"].GetString() ;
            const std::string filepath_v = currentShader["filePath_v"].GetString() ;
            const std::string filepath_f = currentShader["filePath_f"].GetString() ;
            const std::pair<std::string, std::string>  shaderDate({filepath_v,filepath_f});
            _shadersDate.emplace(name,shaderDate); 
        }
    }
    
// ************** A T L A S of texture *********************    
    auto textureAtlas = document.FindMember("textureAtlas");
    
    if (textureAtlas!=document.MemberEnd())
        {  
            for (const auto& currentShit : textureAtlas-> value.GetArray()){
                const std::string name = currentShit["name"].GetString();
                const std::string filePath =currentShit["filePath"].GetString();
//      collect parameters  for   loadTextures(workpath,name,filePath);             
                _textureDate.emplace(name,std::make_pair(workpath,filePath));
                const unsigned int subTextureWidth = currentShit["subTextureWidth"].GetUint();
                const unsigned int subTextureHeight = currentShit["subTextureHeight"].GetUint();
                _subTextSizes.emplace(name,std::make_pair(subTextureWidth,subTextureHeight));
                const auto subTexturesArray = currentShit["subTextureArray"].GetArray(); 
                std::vector<std::string>subTextures;
                size_t arrs= subTexturesArray.Size();
                subTextures.reserve(arrs);
       
                for (const auto& currentSubtextures : subTexturesArray)
                    {
                        subTextures.emplace_back(currentSubtextures.GetString()); 
                    }
                _subTextures.emplace(name,subTextures);
            } 

       }else std::cout << "Something with texturebirdsAtlas?" << std::endl; 

//**************** ONLY TEXTURE FILE    
// there's not name of texture exactly, there is name  like atlas   
    
    auto textures2D = document.FindMember("textures2d");
    
     if (textures2D!=document.MemberEnd())
    {  
        for (const auto& currentShit : textures2D->value.GetArray())
        {
            const std::string name = currentShit["name"].GetString();
            const std::string filePath =currentShit["filePath"].GetString();
//      collect parameters  for   loadTextures(workpath,name,filePath);             
            _textureDate.emplace(name,std::make_pair(workpath,filePath));
        }
        
    }else std::cout << "Something with textures2D ?" << std::endl;
    
//******************** S P R I T E S  **********************************
    auto spritesIt = document.FindMember("sprites");
    if (spritesIt!=document.MemberEnd())
    {
        std::cout<< "@ now load sprites by json @"<< std::endl;
        for (const auto& currentSprite : spritesIt-> value.GetArray())
        {
            const std::string name = currentSprite["name"].GetString() ;
            const std::string atlas = currentSprite["textureAtlas"].GetString() ;
            const std::string shader = currentSprite["shader"].GetString() ;
            const std::string  initialSubTexture = currentSprite["initialSubTexture"].GetString();   
            std::cout<< "just loaded  name:"<< name << "\t atlas:"<< atlas <<" \t shader:"<< shader <<"\t initialSubTexture:"<< initialSubTexture<< std::endl;
            const  ThreeStringsDate threeStringsDate({atlas,shader,initialSubTexture});
            _spriteDate.emplace(name,threeStringsDate);
        }
    }

//******************** A N I M A T E S P R I T E S  **********************************    
// filling two maps : _spriteDate and _anidate, _spriteDate is the same as the simple sprite date, _anidate is animated component   
    auto animateSpritesIt = document.FindMember("animatedSprites");
    if (animateSpritesIt!=document.MemberEnd())
    {
        for (const auto& currentAnimateSprite : animateSpritesIt-> value.GetArray())
        {
            const std::string name = currentAnimateSprite["name"].GetString() ;
            const std::string atlas = currentAnimateSprite["textureAtlas"].GetString() ;
            const std::string shader = currentAnimateSprite["shader"].GetString() ;
            const std::string  initialSubTexture = currentAnimateSprite["initialSubTexture"].GetString();   
            std::cout<< "just loaded  name:"<< name << "\t atlas:"<< atlas <<" \t shader:"<< shader <<"\t initialSubTexture:"<< initialSubTexture<< std::endl;
            const  ThreeStringsDate threeStringsDate({atlas,shader,initialSubTexture});
            _spriteDate.emplace(name,threeStringsDate); 
 
            const auto statesArray = currentAnimateSprite["states"].GetArray();
            statesArray.Size();
            std::map<std::string,std::vector <std::pair<std::string, uint64_t>>> mframes;
            
            for(const auto& currentStateArray : statesArray){
                const std::string stateName = currentStateArray["statesName"].GetString();
                std::vector<std::pair<std::string,uint64_t>>  frames;
                const auto framesArray =  currentStateArray["frames"].GetArray();
                frames.reserve(framesArray.Size());
                for(const auto& currentFrame : framesArray){
                    const std::string subTexture = currentFrame["subTexture"].GetString();
                    const uint64_t duration = currentFrame["duration"].GetUint64();
                    const std::pair<std::string, uint64_t> text_dur= std::make_pair(subTexture,duration); 
                    frames.emplace_back(text_dur); 
                }
                mframes.emplace(stateName,frames);

            }
            _aniDate.emplace(name,mframes);
        }
    }
    return true;    
}

bool ResourceSprite::get_aniDate(const std::string spriteName, std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>& anidate)
{
    
    bool result= false;
    const aniDate::const_iterator it = _aniDate.find(spriteName);
    if(it!= _aniDate.end()){
      
       const std::map<std::string,std::vector<std::pair<std::string,uint64_t>>>  ist = it->second;  
       
       for (auto& currentI : ist)
       {
           std::string statename = currentI.first ;    
          std::vector<std::pair<std::string, uint64_t>> subTexturesDuration = currentI.second;
          anidate.emplace(statename,subTexturesDuration);
       } 
        result = true;
        
    }
    return result;
}


bool  ResourceSprite::get_spriteDate(const std::string spriteName, std::string& shaderName, std::string& textureName, std::string& initialTextName)
{
    
    const spriteDate::const_iterator it = _spriteDate.find(spriteName);
    if(it!= _spriteDate.end()){
    const ThreeStringsDate threeStringsDate = it->second;    
    shaderName = threeStringsDate.shader;
    textureName = threeStringsDate.texture;
    initialTextName = threeStringsDate.initial;
    return true;
    } else
    return false;
}


const std::pair<std::string, std::string>  ResourceSprite::get_shaderDate(const std::string shaderProgName)
{
   const std::map<const std::string ,std::pair<std::string, std::string> >::const_iterator it = _shadersDate.find(shaderProgName);
   if (it!= _shadersDate.end()){
   return it->second;    
} else {
    std::cerr<< "Can't get shader "<< shaderProgName<<" data"<<std::endl;
}
    return {"error first path","error second path"};
}

const std::pair<std::string,std::string> ResourceSprite::get_textureDate(const std::string textureName)
{
    const std::map<const std::string ,std::pair<std::string,std::string>>::const_iterator it = _textureDate.find(textureName);
    if (it!= _textureDate.end()) 
        return it->second;
    else {
        std::cerr<< "Can't get texture "<< textureName<<" data"<<std::endl;
    }
    return {"error first path","error second path"};
}

const std::vector<std::string> ResourceSprite::get_subTextures(const std::string texturesName)
{
    const std::map<const std::string ,std::vector<std::string> >::const_iterator it = _subTextures.find(texturesName);
   if (it!= _subTextures.end()){
   return it->second;    
} else {
    std::cerr<< "Can't find texures "<< texturesName<<"adress"<<std::endl;
}
    return {"notning","nothing"};
    
}





