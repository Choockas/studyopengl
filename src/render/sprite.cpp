
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
                                                  : _pTexture(std::move(pTexture))
                                                   ,_pShaderProgramm(std::move(pShaderProgramm))
    
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
        auto subTexture2D = _pTexture -> getSubtexture2D(std::move(initialSubTexture)); 
        
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
        
        _vertexCoordsBuffer.init(vertexCoords,2*4*sizeof(GLfloat));
        VertexBufferLayout vertexCordsLayout;
        vertexCordsLayout.addElementLayoutFloat(2,false);
        _vertexArray.addBuffer(_vertexCoordsBuffer, vertexCordsLayout);
        
        _textureCoordsBuffer.init(texCoords,2*4*sizeof(GLfloat));
        
        VertexBufferLayout textureCoordsLayout;
        textureCoordsLayout.addElementLayoutFloat(2,false);
        _vertexArray.addBuffer(_textureCoordsBuffer,textureCoordsLayout); 
        
        _indexCoordsBuffer.init(indices,6);
        
        _vertexArray.unbind();
        _indexCoordsBuffer.unbind();

    }
    
    Sprite::~Sprite(){
        
        std::cout<<"sprites delayed "<<std::endl;
        _pShaderProgramm.use_count();
        _pTexture.use_count();
    }

    
    void Sprite::render(const glm::vec2 position, const glm::vec2 size, const float rotation) const
    {
        _pShaderProgramm->use();
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
        _pShaderProgramm->setMatrix4("modelMat",model);
        glActiveTexture(GL_TEXTURE0);
        _pTexture->bind();
        Renderer::draw(_vertexArray,_indexCoordsBuffer,*_pShaderProgramm);
                
    }
}
