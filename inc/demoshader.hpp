#pragma once

#include "glad/glad.h"
#include "glm/vec2.hpp"
#include <memory>
#include <stdio.h>

struct flVec {
    float x;
    float y;
};



class ShaderBuffAndProg{
public:
    ShaderBuffAndProg(const std::string path,const std::string relativePath,const glm::ivec2 windsize);
    ShaderBuffAndProg()=default;
    
    ShaderBuffAndProg(ShaderBuffAndProg& t) = delete;
    ShaderBuffAndProg& operator =(ShaderBuffAndProg&& t)= delete;
    
//     ShaderBuffAndProg& operator = (ShaderBuffAndProg&& shaderBuffers);
//     ShaderBuffAndProg(ShaderBuffAndProg&& shaderBuffers);
    
    virtual ~ShaderBuffAndProg();
    virtual void createDemoShader(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath);
    virtual void useDemoShader();
    virtual  std::shared_ptr<RenderEngine::ShaderProgramm> loadShadersProg(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath );
    std::string get_Filestring(const std::string& filepath );
protected:
    float verticles[9];
    GLfloat colors[9]; 
    GLuint _points_vbo=0;
    GLuint _colors_vbo=0;
    GLuint _vao_primitive_6vf=0;// array for 6 verticles & colorrs layer
    
//     shaderbyStrings _shaderStr; 
    bool _primitiveInitialized =false;
    std::string _path;
    std::string _relativePath;
//     const glm::ivec2 _dsWindsize;
    flVec _fWindsize;
private:
    
    
    std::shared_ptr<RenderEngine::ShaderProgramm> _shaderProgramm;
    
};


class PrimitiveShader:public ShaderBuffAndProg
{
public:
    PrimitiveShader(const std::string path,const std::string relativePath,const glm::ivec2 windsize);
//     PrimitiveShader(PrimitiveShader& t);
    PrimitiveShader& operator=(PrimitiveShader&& primitiveShader);
    PrimitiveShader(PrimitiveShader&& primitiveShader);
    ~PrimitiveShader();
    void createDemoShader(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath) override;
    void useDemoShader() override; 
private:
    std::shared_ptr<RenderEngine::ShaderProgramm> _shadePrimitiveProgram;
    
};


class TransformShader : public ShaderBuffAndProg
{
public:
    TransformShader(const std::string path,const std::string relativePath,const glm::ivec2 windsize);
    TransformShader& operator=(TransformShader&& transformShader);
    TransformShader(TransformShader&& transformShader);
    ~TransformShader();
    void createDemoShader(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath) override;
    void set_grades(const float grades) {_grades=grades;}
    void useDemoShader() override; 
    void chageTrMode(float sval){sval++;} //just dummy
private:
    std::shared_ptr<RenderEngine::ShaderProgramm> _shadeTransformProgram;
    float _grades = 0;
    
};
