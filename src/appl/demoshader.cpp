#include "demoshader.hpp"
#include "shaderprogramm.hpp"

#include <vector>
#define PRIMITIVEOFFSET {0.6f,0.4f}

DemoShader::DemoShader(const std::string path,const std::string relativePath,const  glm::ivec2 windsize) : _path(path) , _relativePath(relativePath) , _fWindsize({static_cast<float>(windsize.x),static_cast<float>(windsize.y)}) 
{
    
        float tverticles[]={
        -0.33f, -0.33f, 0.0f,
        0.33f,  -0.33f, 0.0f,
        -0.33f,  0.33f, 0.0f,
        -0.33f,  0.33f, 0.0f,
        0.33f,   0.33f, 0.0f,
        0.33f,  -0.33f, 0.0f        
    };
    GLfloat colors[]={
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,
        1.0f,0.0f,0.0f
    };
    
    //set up 1-st array, (for vertex)
    glGenBuffers(1,&_points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,_points_vbo);
    //put data
    glBufferData(GL_ARRAY_BUFFER,sizeof(tverticles),tverticles,GL_STATIC_DRAW);
    
    //set up for 2-d array  (for fragments)
    glGenBuffers(1,&_colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,_colors_vbo);
    //put another buffer data 
    glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);
    
    //gen array for shader (vao)
    glGenVertexArrays(1, &_vao_primitive_6vf);
    glBindVertexArray(_vao_primitive_6vf);
    
    // forming vao from both previous
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,_points_vbo);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,_colors_vbo);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,nullptr);
    
    
}

DemoShader::~DemoShader()
{
    std::cout<<"demoshader deleted"<<std::endl;
}


void DemoShader::createPrimitiveShader()
{
    _resourcePrimitive = std::make_unique<ResourcePrimitive>(_path,_relativePath);
    _resourcePrimitive->loadJsonResources();
    
//     auto pSimpleShaderProgram = _resourcePrimitive->getShaderProgram("freeshader1"); 
    _shadep = _resourcePrimitive->getShaderProgram("freeshader1"); 
    _shadep->use();
    _shadep->setVec2("offsete",PRIMITIVEOFFSET);
     _primitiveInitialized = true;

}

void DemoShader::usePrimitiveShader()
{
        //using pointer to shader
    if(_primitiveInitialized){
    _shadep->use();
    
    glBindVertexArray(_vao_primitive_6vf);
    glDrawArrays(GL_TRIANGLES,0,6);
    }
}

void DemoShader::createTransformerShader()
{
        _resourcePrimitive = std::make_unique<ResourcePrimitive>(_path,_relativePath);
    _resourcePrimitive->loadJsonResources();
    
        glm::mat4 projectionMatrix = glm::ortho (0.0f,_fWindsize.x,0.0f,_fWindsize.y,-10.0f,100.0f);
    _shadet = _resourcePrimitive->getShaderProgram("transshader1"); 
    _shadet->use();
    _shadet->setMatrix4("projectionMat", projectionMatrix);
}

void DemoShader::useTransformerShahader(float grades)
{
        const glm::vec2 size= {0.33f*_fWindsize.x,0.33f*_fWindsize.y};
    _shadet->use();
    glBindVertexArray(_vao_primitive_6vf);
    glm::mat4 modelMatrix_t00  = glm::mat4(1.0f);
    modelMatrix_t00   = glm::translate(modelMatrix_t00  ,glm::vec3(0.5f*_fWindsize.x,0.5f*_fWindsize.y,0.f));
    

    modelMatrix_t00  = glm::translate(modelMatrix_t00 ,glm::vec3(100.0f,100.0f,0.0f));  
    modelMatrix_t00  = glm::scale(modelMatrix_t00  ,glm::vec3(size,.5f));
    _shadet->setMatrix4("modelMat",modelMatrix_t00 );
    
    glLineWidth(3); 
    glDrawArrays( GL_TRIANGLES,0,6);
    modelMatrix_t00  = glm::rotate(modelMatrix_t00 ,glm::radians(grades/2),glm::vec3(0.f,0.f,1.f)); 
    modelMatrix_t00   = glm::translate(modelMatrix_t00  ,glm::vec3(.5f,.5f,0.f));
    modelMatrix_t00  = glm::scale(modelMatrix_t00  ,glm::vec3(0.5f,0.5f,.5f));
    _shadet->setMatrix4("modelMat",modelMatrix_t00 );
    glLineWidth(3); 
    glDrawArrays( GL_TRIANGLES,0,6);
    
    glm::mat4 modelMatrix_t01  = glm::mat4(1.0f);

    modelMatrix_t01   = glm::translate(modelMatrix_t01 ,glm::vec3(0.5f*_fWindsize.x,0.5f*_fWindsize.y,0.f));
    modelMatrix_t01   = glm::rotate(modelMatrix_t01  ,glm::radians(grades),glm::vec3(0.f,0.f,1.f));
    modelMatrix_t01   = glm::translate(modelMatrix_t01 ,glm::vec3(0.5f*size.x,0.5f*size.y,0.f));
    
    modelMatrix_t01  = glm::scale(modelMatrix_t01  ,glm::vec3(100.f,100.f,.05f));
    modelMatrix_t01   = glm::translate(modelMatrix_t01 ,glm::vec3(.3,1.0f,0.f));
    _shadet->setMatrix4("modelMat",modelMatrix_t01 );
    glDrawArrays( GL_LINE_LOOP,0,3);
    glDrawArrays( GL_TRIANGLES,3,3);
    modelMatrix_t01   = glm::rotate(modelMatrix_t01  ,-1.0f*glm::radians(grades*2),glm::vec3(0.f,0.f,1.f));
    
    _shadet->setMatrix4("modelMat",modelMatrix_t01 );
    glBindVertexArray(_vao_primitive_6vf);
    
    glDrawArrays( GL_LINE_LOOP,0,3);
    glDrawArrays( GL_TRIANGLES,3,3);
    glDrawArrays(GL_LINE,0,6);
}


