#include "resourceaccess.hpp"
#include <fstream>
#include <sstream>


ResourceAcces::~ResourceAcces()
{
}

ResourceAcces::ResourceAcces()
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


ResourceSprite::ResourceSprite()
{
}

ResourceSprite::~ResourceSprite()
{
}

std::shared_ptr<RenderEngine::ShaderProgramm> ResourceSprite::getShaderProgram(const std::string& shaderName)
{
    return nullptr;
}

std::shared_ptr<RenderEngine::Sprite> ResourceSprite::getSprites(const std::string& spriteName)
{
    return nullptr;
}


std::shared_ptr<RenderEngine::Texture2D> ResourceSprite::getTextures(const std::string& textureName)
{
    return nullptr;
}

bool ResourceSprite::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
    return true;
}

std::shared_ptr<RenderEngine::Sprite> ResourceSprite::loadSprites(const std::string& spriteName, const std::string& textureName, const std::string& shaderName, const std::string& subtextureName)
{
    return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceSprite::loadTextures(const std::string& resourcePath, const std::string& textureName, const std::string& texturePath)
{
    return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceSprite::loadTextureAtlas(const std::string& resourcePath, const std::string& textureName, const std::string& stexturePath, const std::vector<std::string> subTextures, const unsigned int subTexwidth, const unsigned int subTexheight)
{
    return nullptr;
}




