#pragma once

#include "sprite.hpp"
#include <map>
#include <vector>

namespace RenderEngine {
    class Texture2D;
    class ShaderProgramm;
    
    
    class AnimateSprite: public Sprite{
    public:
        AnimateSprite ( std::shared_ptr<Texture2D>  pTexture
                 ,std::string initialSubTexture
                 ,std::shared_ptr<ShaderProgramm> pShaderProgramm
                
               );
        ~AnimateSprite();
        void insertState(std::string state,std::vector<std::pair<std::string,uint64_t >> subTexturesDuration);
        void render(const glm::vec2 position, const glm::vec2 size, const float rotation) const override ;
        void setState(const std::string& newState);
        void update(const uint64_t delta ); 
        
    private:
        std::map<std::string,std::vector<std::pair<std::string,uint64_t>>> m_statesMap;
        size_t _currentFrame = 0;
        uint64_t  _currentAnimationTime = 0;
        std::map<std::string,std::vector<std::pair<std::string,uint64_t>>>::const_iterator m_pCurrentAnimationDuration;
        mutable bool _dirty=false;
    };
 
}
