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
     
 }
        

 FramedSprite::~FramedSprite()
 {
     std::cout << "framed sprite releazed"<< std::endl;
}

void FramedSprite::insertState(const std::string& statesName,const std::string&   subTexturesState)
{
        m_states.emplace(statesName, subTexturesState);
}




void FramedSprite::update(const std::string state){
  m_currentFrame= m_states.find(state)->second;
  m_dirty = true;  
}

/*
void AnimateSprite::update(const uint64_t delta) 
{
    if(m_pCurrentAnimationDuration != m_statesMap.end()){
        m_currentAnimationTime+= delta;
        while(m_currentAnimationTime>= m_pCurrentAnimationDuration->second[m_currentFrame].second){
            m_currentAnimationTime -=m_pCurrentAnimationDuration->second[m_currentFrame].second;
            ++m_currentFrame;
            m_dirty = true;
        
        if(m_currentFrame == m_pCurrentAnimationDuration->second.size()){
            m_currentFrame =0;
        }
        }
    }
}
*/

void FramedSprite::render(const glm::vec2 position, const glm::vec2 size, const float rotation) const 
{
    if (m_dirty){
        
        auto subTexture2D = _pTexture -> getSubtexture2D(m_currentFrame); 
        
        const GLfloat texCoords[] ={
            subTexture2D.leftBottomUV.x, subTexture2D.leftBottomUV.y,
            subTexture2D.leftBottomUV.x, subTexture2D.rightTopUV.y,
            subTexture2D.rightTopUV.x,   subTexture2D.rightTopUV.y,
            subTexture2D.rightTopUV.x,   subTexture2D.leftBottomUV.y,
        };
        
        _textureCoordsBuffer.update(texCoords,2*4*sizeof(GLfloat)); 
        
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); 
        m_dirty = false;
        
    }
    Sprite::render(position, size, rotation);
    
}

}
