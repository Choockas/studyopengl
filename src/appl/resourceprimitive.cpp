#include "resourceprimitive.hpp"
#include "shaderprogramm.hpp"

ResourcePrimitive::ResourcePrimitive(const std::string path,const std::string resource_path ) :_resultPath(resource_path)
{
    set_path(path);
}

ResourcePrimitive::~ResourcePrimitive()
{
}


std::shared_ptr<RenderEngine::ShaderProgramm> ResourcePrimitive::getShaderProgram(const std::string& shaderName)
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

bool ResourcePrimitive::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
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
            loadShaders(name, filepath_v,filepath_f);            
        }
    }
    return true;
}

