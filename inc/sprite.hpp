#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>
#include <string>
#include "vertexbuffers.hpp"
#include "indexbuffers.hpp"
#include "vertexarray.hpp"


namespace RenderEngine {
    class Texture2D;
    class ShaderProgramm;
    
    class Sprite{
    public:
        Sprite (std::shared_ptr<Texture2D>  pTexture,
                std::string initialSubTexture
                ,std::shared_ptr<ShaderProgramm> pShaderProgramm

               );
        virtual ~ Sprite();
        Sprite(Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete; 
         virtual void render(const glm::vec2 position, const glm::vec2 size, const float rotation) const;
         
    protected:
        std::shared_ptr<Texture2D> m_pTexture;
        std::shared_ptr<ShaderProgramm> m_pShaderProgramm;
       
        
        VertexArray m_vertexArray;
        VertexBuffer m_vertexCoordsBuffer;
        VertexBuffer m_textureCoordsBuffer;
        IndexBuffer m_indexCoordsBuffer;
        

    };
 
}

