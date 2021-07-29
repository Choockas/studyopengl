#pragma once

#include "glad/glad.h"
#include "glm/vec2.hpp"
#include <memory>
#include <stdio.h>

struct flVec {
    float x;
    float y;
};



class ShaderBuffers{
public:
    ShaderBuffers(const std::string path,const std::string relativePath,const glm::ivec2 windsize);
    virtual ~ShaderBuffers();
    virtual void createDemoShader(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath);
    virtual void useDemoShader();
    virtual  std::shared_ptr<RenderEngine::ShaderProgramm> loadShaders(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath );
    std::string get_Filestring(const std::string& filepath );
protected:
    float verticles[9];
    GLfloat colors[9]; 
    GLuint _points_vbo=0;
    GLuint _colors_vbo=0;
    GLuint _vao_primitive_6vf=0;// array for 6 verticles & colorrs layer
    
//     shaderbyStrings _shaderStr; 
    bool _primitiveInitialized =false;
    const std::string _path;
    const std::string _relativePath;
//     const glm::ivec2 _dsWindsize;
    const flVec _fWindsize;
private:
    
    
    std::shared_ptr<RenderEngine::ShaderProgramm> _shader;
    
};


class PrimitiveShader:public ShaderBuffers
{
public:
    PrimitiveShader(const std::string path,const std::string relativePath,const glm::ivec2 windsize);
    ~PrimitiveShader();
    void createDemoShader(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath) override;
    void useDemoShader() override; 
private:
    std::shared_ptr<RenderEngine::ShaderProgramm> _shadep;
    
};


class TransformShader : public ShaderBuffers
{
public:
    TransformShader(const std::string path,const std::string relativePath,const glm::ivec2 windsize);
    ~TransformShader();
    void createDemoShader(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath) override;
    void set_grades(const float grades) {_grades=grades;}
    void useDemoShader() override; 
    void chageTrMode(float sval){sval++;} //just dummy
private:
    std::shared_ptr<RenderEngine::ShaderProgramm> _shadet;
    float _grades = 0;
    
};
