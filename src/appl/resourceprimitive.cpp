#include "resourceprimitive.hpp"
#include "shaderprogramm.hpp"

ResourcePrimitive::ResourcePrimitive(const std::string path,const std::string resource_path ) :_resultPath(resource_path)
{
    set_path(path);
}

ResourcePrimitive::~ResourcePrimitive()
{
    
}


// std::shared_ptr<RenderEngine::ShaderProgramm> ResourcePrimitive::getShaderProgram(const std::string& shaderName)
// {
//         ShaderProgramsMap::const_iterator it=_shaderPrograms.find(shaderName);
//     if(it!=_shaderPrograms.end()){
//         return it->second;
//     }
//     std::cerr<<"Can't find the shader program "
//     <<shaderName
//     <<std::endl;
//     return nullptr;
// }


void ResourcePrimitive::loadShaderString(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
    ShaderbyStrings shbs;
    shbs.nameShaderProgramm = shaderName;
    shbs.vertexName = vertexPath;
    shbs.fragmentName = fragmentPath;
    _demoShaders.emplace_back(shbs); 
}


std::string ResourcePrimitive::getNameSPstring(const int ind ) const
{
    const std::string namePS = _demoShaders.at(ind).nameShaderProgramm;
    return namePS;
}



std::string ResourcePrimitive::getNameVertexstring(const int ind) const
{
    return _demoShaders.at(ind).vertexName;
}


std::string ResourcePrimitive::getNameFragmentstring(const int ind) const
{
    return _demoShaders.at(ind).fragmentName;
}


bool ResourcePrimitive::loadJsonResources()
{
        const std::string JSONstring = getFileString(_resultPath);
    
    if (JSONstring.empty())
    {
        std::cerr << "No JSON resources file"<< _resultPath<<std::endl;
        return false;
    }
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
            const std::string filepath_v = currentShader["filepathvertex"].GetString() ;
            const std::string filepath_f = currentShader["filepathfrag"].GetString() ;
            loadShaderString(name, filepath_v,filepath_f);            
        }
    }
    return true;
}

