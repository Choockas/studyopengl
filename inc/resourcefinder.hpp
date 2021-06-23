#pragma once
#include "resourceaccess.hpp"
#include "document.h"
#include "error/en.h"
#include <memory>
#include <vector>
#include <map>

class ResourceFinder:public ResourceAcces
{
public:
    ResourceFinder(std::string path,std::string resource_path );
//     ~ResourceFinder();
    bool loadJsonResources() override;
    std::string getJson(const std::string localPath); 
    std::string get_resultPath(const std::string resourceName);
private:   
   rapidjson::Document _document;
   std::map<const std::string, std::string> _resourcesMap;
   std::string _resultPath; 
};


