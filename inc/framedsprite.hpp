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
        void insertState( const std::string& statesName, const std::string&  subTexturesState);
        void render(const glm::vec2 position, const glm::vec2 size, const float rotation) const override ;
        void update(const std::string state);
        
    private:
        std::map<std::string,std::string> m_states;
        std::string m_currentFrame ;
        
        mutable bool m_dirty=false;
    };
 
}
