#include "resourcemanager.hpp"
#include "renderer.hpp"
#include <fstream>
#include <sstream>

ResourceManager::ResourceManager(){
    
    
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
    
    return true;
}

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

std::string ResourceManager::getFileString(const std::string& relativePath)
{
    std::ifstream f;
    f.open(relativePath+"/"+relativePath,std::ios::in | std::ios::binary);
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




void ResourceManager::managerInit(const std::string& exepath)
{
    loadJsonResources(exepath);
}



Accesories::Accesories()
{
}



bool Accesories::loadJsonResources(const std::string& resourcePath)
{
    
    return true;
}

