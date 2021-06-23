#pragma once
#include "glad/glad.h"
#include "resourceprimitive.hpp"

class DemoShader{
public:
    DemoShader(const std::string path,const std::string relativePath);
    virtual ~DemoShader();
    void crteateShader();
    void useShader();
private:
    float verticles[9];
    GLfloat colors[9]; 
    GLuint _points_vbo=0;
    GLuint _colors_vbo=0;
    GLuint _vao_primitive_6vf=0;// array for 6 verticles & colorrs layer
    std::unique_ptr<ResourcePrimitive>   _resourcePrimitive; 
    std::shared_ptr<RenderEngine::ShaderProgramm> _shadep;
    bool _primitiveInitialized =false;
    std::string _path;
    std::string _relativePath;
};
