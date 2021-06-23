#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <glm/mat4x4.hpp>
#include "glm/gtc/type_ptr.hpp"


namespace RenderEngine{

    //const char* vertex_shader;
    class ShaderProgramm{
        
    public:
        ShaderProgramm(const std::string &vertexShader, const std::string &fragmentShader);
        ~ShaderProgramm();
        ShaderProgramm() = delete;
        
        
        ShaderProgramm& operator = (const ShaderProgramm&)=delete;
        
        ShaderProgramm& operator = (ShaderProgramm&& shaderProgramm) noexcept;
        ShaderProgramm(ShaderProgramm&& shaderProgramm) noexcept;
        ShaderProgramm(ShaderProgramm&)= delete;
        bool isCompiled() const {return m_isCompiled;}
        
        void use() const;
        
        void setInt(const std::string& name,const GLint value);
        void setFloat(const std::string &name, const float value) const;
        void setVec2(const std::string &name,const glm::vec2 value) const; 
        void setMatrix4(const std::string& name,const glm::mat4& matrix);
    private:
       bool CreateShader(const std::string& source,const GLenum shaderType, GLuint& shaderID);
        GLint m_isCompiled=false;
        GLuint m_ID;
        
    };
    


}
