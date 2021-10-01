#include "animatesprite.hpp"
#include "texture2D.hpp"
#include <iostream>

namespace RenderEngine{

 AnimateSprite::AnimateSprite ( std::shared_ptr<Texture2D>  pTexture
                ,std::string initialSubTexture
                ,std::shared_ptr<ShaderProgramm> pShaderProgramm)
                 : Sprite(std::move(pTexture)
                          ,std::move(initialSubTexture)
                          ,std::move(pShaderProgramm)
                                               )
                
 {
     m_pCurrentAnimationDuration = m_statesMap.end();
     std::cout<< "animated sprite created "<<std::endl;
 }

 AnimateSprite ::~AnimateSprite()
 {
     std::cout << "animate sprite releazed"<< std::endl;
}

void AnimateSprite::insertState(std::string state, std::vector<std::pair<std::string, uint64_t > > subTexturesDuration)
{
        m_statesMap.emplace(std::move(state),std::move(subTexturesDuration));
        
}


void AnimateSprite::setState(const std::string& newState)
{
    auto it = m_statesMap.find(newState);
    if (it==m_statesMap.end()){
        std::cout << "cant find state "<<newState<<std::endl;
        return;
    }
    if(it!= m_pCurrentAnimationDuration){
        _currentAnimationTime =0;
        _currentFrame = 0;
        m_pCurrentAnimationDuration =it; 
        _dirty = true; 
    }
    
}

void AnimateSprite::update(const uint64_t delta) 
{
    if(m_pCurrentAnimationDuration != m_statesMap.end()){
        _currentAnimationTime+= delta;
        while(_currentAnimationTime>= m_pCurrentAnimationDuration->second[_currentFrame].second){
            _currentAnimationTime -=m_pCurrentAnimationDuration->second[_currentFrame].second;
            ++_currentFrame;
            _dirty = true;
        
        if(_currentFrame == m_pCurrentAnimationDuration->second.size()){
            _currentFrame =0;
        }
        }
    }
}


void AnimateSprite::render(const glm::vec2 position, const glm::vec2 size, const float rotation) const 
{
    if (_dirty){
        
        auto subTexture2D = _pTexture -> getSubtexture2D(m_pCurrentAnimationDuration->second[_currentFrame].first); 
        
        const GLfloat texCoords[] ={
            //U-V
            subTexture2D.leftBottomUV.x, subTexture2D.leftBottomUV.y,
            subTexture2D.leftBottomUV.x, subTexture2D.rightTopUV.y,
            subTexture2D.rightTopUV.x,   subTexture2D.rightTopUV.y,
            subTexture2D.rightTopUV.x,   subTexture2D.leftBottomUV.y,
        };
        _textureCoordsBuffer.update(texCoords,2*4*sizeof(GLfloat)); 
        
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        _dirty = false;
    }
    Sprite::render(position, size, rotation);
    
}

}
