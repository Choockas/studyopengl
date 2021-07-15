#pragma once

#include "glad/glad.h"
#include "glm/vec2.hpp"
#include "resourceprimitive.hpp"

struct flVec {
    float x;
    float y;
};

class DemoShader{
public:
    DemoShader(const std::string path,const std::string relativePath,const glm::ivec2 windsize);
    virtual ~DemoShader();
    void createPrimitiveShader();
    void usePrimitiveShader();
    void createTransformerShader();
    void useTransformerShahader(float grades);
private:
    float verticles[9];
    GLfloat colors[9]; 
    GLuint _points_vbo=0;
    GLuint _colors_vbo=0;
    GLuint _vao_primitive_6vf=0;// array for 6 verticles & colorrs layer
    std::unique_ptr<ResourcePrimitive>   _resourcePrimitive; 
    std::shared_ptr<RenderEngine::ShaderProgramm> _shadep;
    std::shared_ptr<RenderEngine::ShaderProgramm> _shadet;
    bool _primitiveInitialized =false;
    std::string _path;
    std::string _relativePath;
//     const glm::ivec2 _dsWindsize;
    const flVec _fWindsize;
};
