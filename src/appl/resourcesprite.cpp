#include "resourcesprite.hpp"
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"




ResourceManager::ResourceManager(const std::string path,const std::string resourcePath):ResourceAcces(path),_resourcePath(resourcePath)
{
    
    std::cout<<"resource m created"<<std::endl;
}

ResourceManager::~ResourceManager()
{
}


bool ResourceManager::loadJsonResources() 
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
    

    
    auto shadersIt = document.FindMember("shaders");
    if (shadersIt!=document.MemberEnd())
    {
        for (const auto& currentShader : shadersIt-> value.GetArray())
        {
            const std::string name = currentShader["name"].GetString() ;
            const std::string filepath_v = currentShader["filePath_v"].GetString() ;
            const std::string filepath_f = currentShader["filePath_f"].GetString() ;
            const std::pair<std::string, std::string>  shaderDate({filepath_v,filepath_f});
            
//             loadShaders(name, filepath_v,filepath_f);  
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
 /*           auto pAnimatedSprite = loadAnimateSprites(name,atlas,shader,initialSubTexture);
            if(! pAnimatedSprite ){
                std::cerr << "Can't load animatesprite (initial) "<< initialSubTexture << std::endl;
                continue;
            }  */   
 
            const auto statesArray = currentAnimateSprite["states"].GetArray();
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
//                 pAnimatedSprite->insertState(stateName, std::move(frames));
            }
            _aniDate.emplace(name,mframes);
        }
    }
    
    return true;    
}
// statesname, {pair1,pair2}  pair{string,uint64_t}

const std::map<std::string,std::vector<std::pair<std::string,uint64_t>>> ResourceManager::get_aniDate(const std::string spriteName)
{
    const aniDate::const_iterator it = _aniDate.find(spriteName);
    if(it!= _aniDate.end()){
        
        return it->second;
    }
    return it->second;
    
}



bool  ResourceManager::get_spriteDate(const std::string spriteName, std::string& shaderName, std::string& textureName, std::string& initialTextName)
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


const std::pair<std::string, std::string>  ResourceManager::get_shaderDate(const std::string shaderProgName)
{
   const std::map<const std::string ,std::pair<std::string, std::string> >::const_iterator it = _shadersDate.find(shaderProgName);
   if (it!= _shadersDate.end()){
   return it->second;    
} else {
    std::cerr<< "Can't get shader "<< shaderProgName<<" data"<<std::endl;
}
    return {"error first path","error second path"};
}

const std::pair<std::string,std::string> ResourceManager::get_textureDate(const std::string textureName)
{
//     const TwoStringsDate errSD{"",""}; 
    const std::map<const std::string ,std::pair<std::string,std::string>>::const_iterator it = _textureDate.find(textureName);
    if (it!= _textureDate.end()) 
        return it->second;
    else {
        std::cerr<< "Can't get texture "<< textureName<<" data"<<std::endl;
    }
    return {"error first path","error second path"};
}

const std::vector<std::string> ResourceManager::get_subTextures(const std::string texturesName)
{
    const std::map<const std::string ,std::vector<std::string> >::const_iterator it = _subTextures.find(texturesName);
   if (it!= _subTextures.end()){
   return it->second;    
} else {
    std::cerr<< "Can't find texures "<< texturesName<<"adress"<<std::endl;
}
    return {"notning","nothing"};
    
}





