#pragma once
#include "vertexarray.hpp"
#include "indexbuffers.hpp"
#include "shaderprogramm.hpp"

namespace RenderEngine{
    
    class Renderer{
    public:      
        static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgramm& shaderProgramm);
        static void setClearColor(float r,float g, float b, float a);
        static void clear();
        static void setViewPort(unsigned int width, unsigned int hight, unsigned int leftOffset=0, unsigned int bottomOffset=0);
//         static void setWindTitle();
        static std::string getRendererStr();
        static std::string getVersionString();
        static std::string getShaderVersionString();
    private:
        
    };
}
