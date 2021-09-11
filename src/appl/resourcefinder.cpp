#include "resourcefinder.hpp"


ResourceFinder::ResourceFinder(const std::string path, std::string resource_path) : ResourceAcces(path), _resultPath(resource_path)
{
}


bool ResourceFinder::loadJsonResources() 
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
        
         auto resourceIt = document.FindMember("inits");
    
    if (resourceIt!=document.MemberEnd())
    {
        for (const auto& currentResource : resourceIt-> value.GetArray())
        {
            const std::string name = currentResource["name"].GetString() ;
            const std::string filepath_j = currentResource["path"].GetString() ;            
            _resourcesMap.emplace(name,filepath_j);
        }
    }
    return true;
}

std::string ResourceFinder::get_resultPath(const std::string resourceName)
{
     std::map<const std::string, std::string> ::const_iterator it=_resourcesMap.find(resourceName);
    if(it!=_resourcesMap.end()){
        return it->second;
    }
    std::cerr<<"Can't find resource " <<resourceName <<std::endl;
    return "";
}
