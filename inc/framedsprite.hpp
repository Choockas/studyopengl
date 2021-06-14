#pragma once

#include "sprite.hpp"
#include <map>
#include <vector>

namespace RenderEngine {
    class Texture2D;
    class ShaderProgramm;
    
    class FramedSprite: public Sprite{
    public:
        FramedSprite ( std::shared_ptr<Texture2D>  pTexture
                 ,std::string initialSubTexture
                 ,std::shared_ptr<ShaderProgramm> pShaderProgramm
                
               );
        ~FramedSprite();
        void insertState(std::string state,std::vector<std::pair<std::string,uint64_t >> subTexturesDuration);
        void render(const glm::vec2 position, const glm::vec2 size, const float rotation) const override ;
        void setState(std::string& newState);
        
        
    private:
        std::map<std::string,std::vector<std::pair<std::string,uint64_t>>> m_statesMap;
        size_t m_currentFrame = 0;
        mutable bool m_dirty=false;
    };
 
}
