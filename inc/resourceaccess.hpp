#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <map>



class ResourceAcces
{
public:
    ResourceAcces(const std::string workpath);
    virtual ~ResourceAcces();
    virtual bool loadJsonResources()=0;
    std::string getFileString(const std::string& relativePath);
    std::string get_execpath()const{return _path;}
//     void set_path(const std::string path){_path=path;};
    
private:;
  const std::string _path;
    
    
};

