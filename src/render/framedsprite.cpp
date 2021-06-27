#include "framedsprite.hpp"
#include "texture2D.hpp"
#include <iostream>

namespace RenderEngine{

 FramedSprite::FramedSprite( std::shared_ptr<Texture2D>  pTexture
                ,std::string initialSubTexture
                ,std::shared_ptr<ShaderProgramm> pShaderProgramm)
                 : Sprite(std::move(pTexture)
                          ,std::move(initialSubTexture)
                          ,std::move(pShaderProgramm)
                                               )
                
 {
     
     std::cout<< "framed sprite  created "<<std::endl;
 }
        

 FramedSprite::~FramedSprite()
 {
     std::cout << "framed sprite releazed"<< std::endl;
}

void FramedSprite::insertState(std::string statesName, std::string   subTexturesState)
{
        m_states.emplace(statesName, subTexturesState);
}


void FramedSprite::setState(std::string& newState)
{
    auto it = m_states[newState];
//     if (it==m_states.end()){
//         std::cout << "cant find state "<<newState<<std::endl;
//         return;
//     }
    m_currentFrame = it.c_str();
    m_dirty = true;
    
}

void FramedSprite::update(){
    
    
}


void FramedSprite::render(const glm::vec2 position, const glm::vec2 size, const float rotation) const 
{
    if (m_dirty){
        
        auto subTexture2D = m_pTexture -> getSubtexture2D(m_currentFrame); 
        
        const GLfloat texCoords[] ={
            //U-V
            subTexture2D.leftBottomUV.x, subTexture2D.leftBottomUV.y,
            subTexture2D.leftBottomUV.x, subTexture2D.rightTopUV.y,
            subTexture2D.rightTopUV.x,   subTexture2D.rightTopUV.y,
            subTexture2D.rightTopUV.x,   subTexture2D.leftBottomUV.y,
        };
        m_textureCoordsBuffer.update(texCoords,2*4*sizeof(GLfloat)); 
        
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        m_dirty = false;
    }
    Sprite::render(position, size, rotation);
    
}

}
