#pragma once 
#include "resourceaccess.hpp"
#include "document.h"
#include "error/en.h"
#include <stdio.h>
#include <memory>
#include <map>

namespace RenderEngine{
    class ShaderProgramm;
}

class ResourcePrimitive: public ResourceAcces
{
public:
    ResourcePrimitive(const std::string path,const std::string resource_path );
    ~ResourcePrimitive();
    bool loadJsonResources() override;
    std::shared_ptr<RenderEngine::ShaderProgramm> getShaderProgram(const std::string& shaderName);
    bool loadShaders(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath );
    
private:
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgramm>> ShaderProgramsMap;
    ShaderProgramsMap _shaderPrograms;
    rapidjson::Document _document;
    std::string _resultPath;
    
};
