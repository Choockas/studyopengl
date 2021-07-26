#pragma once 
#include "resourceaccess.hpp"
#include "document.h"
#include "error/en.h"
#include <stdio.h>


struct ShaderbyStrings{
    std::string  nameShaderProgramm;
    std::string vertexName;
    std::string fragmentName;    
};


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
    void loadShaderString(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath);
    std::string  getNameSPstring(const int) const;
    std::string getNameVertexstring(const int ind) const ;
    std::string getNameFragmentstring(const int ind) const ;
private:
    std::vector<ShaderbyStrings> _demoShaders;
    
    
//     typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgramm>> ShaderProgramsMap;
//     ShaderProgramsMap _shaderPrograms;
    rapidjson::Document _document;
    std::string _resultPath;
    
};
