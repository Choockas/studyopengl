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
