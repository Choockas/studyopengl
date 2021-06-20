#pragma once
#include <iostream>

class ResourceAcces
{
public:
    ResourceAcces();
    virtual ~ResourceAcces();
    virtual bool loadJsonResources()=0;
    std::string getFileString(const std::string& relativePath);
    std::string get_path()const{return _path;}
    void set_path(std::string path){_path=path;};
    
private:;
    std::string _path;
    
    
};
