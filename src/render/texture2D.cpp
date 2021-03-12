#include "texture2D.hpp"


namespace RenderEngine{
    
    
   
Texture2D::Texture2D(const GLuint width,
              const GLuint hight,
              const unsigned char* data,
              const GLuint chanals,
              const GLenum filter ,
              const GLenum wrapMode): m_width(width), m_hight(hight)
{
    switch(chanals){
        case 3:
            m_mode = GL_RGB;
            break;
        case 4:
            m_mode = GL_RGBA;
            break;
        default:
            m_mode = GL_RGBA;
            break;
    }
    glGenTextures(1,&m_ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,m_ID);
    glTexImage2D(GL_TEXTURE_2D,0, m_mode,m_width,m_hight,0,m_mode,GL_UNSIGNED_BYTE,data);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, filter);  
    glBindTexture(GL_TEXTURE_2D,0);
    std::cout<< "just created texture "<<m_ID<< std::endl;
}

void Texture2D::bind() const
{
    glBindTexture(GL_TEXTURE_2D,m_ID);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1,&m_ID);
    std::cout << "destructor of texture "<<m_ID<<std::endl;
}

Texture2D& Texture2D::operator=(Texture2D&& texture2D)
{
    glDeleteTextures(1,&m_ID);
    m_ID = texture2D.m_ID;
    texture2D.m_ID = 0;
    m_mode = texture2D.m_mode;
    m_width = texture2D.m_width;
    m_hight = texture2D.m_hight;
    return *this;
}

 Texture2D::Texture2D(Texture2D&& texture2D)
 {
     m_ID = texture2D.m_ID;
    texture2D.m_ID = 0;
    m_mode = texture2D.m_mode;
    m_width = texture2D.m_width;
    m_hight = texture2D.m_hight;  
     
}

void Texture2D::addSubTextures2D(std::string name, glm::vec2& leftBottomUV, glm::vec2& rightTopUV)
{
    m_subTextures2D.emplace(std::move(name),SubTexture2D(leftBottomUV,rightTopUV));
    
}

const RenderEngine::Texture2D::SubTexture2D & Texture2D::getSubtexture2D(const std::string name) const
{
 auto it = m_subTextures2D.find(name);
 if(it!= m_subTextures2D.end()){
     return it->second;
}
  const static SubTexture2D defaultSubTextures;  
  return defaultSubTextures; 
}

    
    
    
}


