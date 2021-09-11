
#include "shaderprogramm.hpp"
#include "texture2D.hpp"
#include "sprite.hpp"


#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "renderer.hpp"

namespace RenderEngine{
    
    Sprite::Sprite(     std::shared_ptr<Texture2D>  pTexture
                                       ,std::string initialSubTexture 
                   ,std::shared_ptr<ShaderProgramm> pShaderProgramm = nullptr)
                                                  : m_pTexture(std::move(pTexture))
                                                   ,m_pShaderProgramm(std::move(pShaderProgramm))
    
    {
        // 1-2
        // |/|
        // 0-3
        const GLfloat vertexCoords[] ={
            //x-y     
            0.f,0.f,
            0.f,1.f,
            1.f,1.f,
            1.f,0.f,
            
        };
//         m_pTexture->getSubtexture2D(std::move(initialSubTexture));
        auto subTexture2D = m_pTexture -> getSubtexture2D(std::move(initialSubTexture)); 
        
        const GLfloat texCoords[] ={
            //U-V
            subTexture2D.leftBottomUV.x, subTexture2D.leftBottomUV.y,
            subTexture2D.leftBottomUV.x, subTexture2D.rightTopUV.y,
            subTexture2D.rightTopUV.x,   subTexture2D.rightTopUV.y,
            subTexture2D.rightTopUV.x,   subTexture2D.leftBottomUV.y,
        };
        
        const GLuint indices[] ={
            0,1,2,
            2,3,0             
        };
        
        m_vertexCoordsBuffer.init(vertexCoords,2*4*sizeof(GLfloat));
        VertexBufferLayout vertexCordsLayout;
        vertexCordsLayout.addElementLayoutFloat(2,false);
        m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCordsLayout);
        
        m_textureCoordsBuffer.init(texCoords,2*4*sizeof(GLfloat));
        
        VertexBufferLayout textureCoordsLayout;
        textureCoordsLayout.addElementLayoutFloat(2,false);
        m_vertexArray.addBuffer(m_textureCoordsBuffer,textureCoordsLayout); 
        
        m_indexCoordsBuffer.init(indices,6);
        
        m_vertexArray.unbind();
        m_indexCoordsBuffer.unbind();

    }
    
    Sprite::~Sprite(){
        
        std::cout<<"sprites delayed "<<std::endl;
        m_pShaderProgramm.use_count();
        m_pTexture.use_count();
    }

    
    void Sprite::render(const glm::vec2 position, const glm::vec2 size, const float rotation) const
    {
        m_pShaderProgramm->use();
//         if (position.x == 20.0) 
//         {
//             std::cout << "20 \t" <<std::endl;
//         }
        glm::mat4 model(1.f);
        model = glm::translate(model,glm::vec3(position,0.f));
        model = glm::translate(model,glm::vec3(0.5f*size.x,0.5f*size.y,0.f));
        model = glm::rotate(model,glm::radians(rotation),glm::vec3(0.f,0.f,1.f));
        model = glm::translate(model,glm::vec3(-0.5f*size.x,-0.5f*size.y,0.f));
        model = glm::scale(model,glm::vec3(size,1.f));
        
        //m_vertexArray.bind();
        m_pShaderProgramm->setMatrix4("modelMat",model);
        glActiveTexture(GL_TEXTURE0);
        m_pTexture->bind();
        Renderer::draw(m_vertexArray,m_indexCoordsBuffer,*m_pShaderProgramm);
                
    }
}
