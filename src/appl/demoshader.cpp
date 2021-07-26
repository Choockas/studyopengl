#include "shaderprogramm.hpp"
#include "demoshader.hpp"
#include <fstream>
#include <sstream>

#include <vector>
#define SIMPLEOFFSET {0.6f,0.4f}

ShaderBuffers::ShaderBuffers(const std::string path,const std::string relativePath,const  glm::ivec2 windsize) : _path(path) , _relativePath(relativePath) , _fWindsize({static_cast<float>(windsize.x),static_cast<float>(windsize.y)}) 
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

ShaderBuffers::~ShaderBuffers()
{
    std::cout<<"demoshader deleted"<<std::endl;
}


void ShaderBuffers::createDemoShader(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath)
{
        _shader = loadShaders(shaderName,vertexPath,fragmentPath); 
    _shader->use();
    
     _primitiveInitialized = true;
}

void ShaderBuffers::useDemoShader()
{
    
    std::cout<<"using parents class"<<std::endl;
}


std::string ShaderBuffers::get_Filestring(const std::string& filepath)
{

    std::ifstream f;
    f.open(filepath,std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cerr<<"Failed to open "<< filepath <<std::endl;
        return std::string();
    }
    std::stringstream buffer;
    buffer<<f.rdbuf();
    std::cout<< "getting string from "<< filepath <<std::endl;
    return buffer.str();

}



 std::shared_ptr<RenderEngine::ShaderProgramm> ShaderBuffers::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{

       std::string vertexString = get_Filestring(vertexPath);
    if (vertexString.empty()){
        std::cerr<<"No vertex shader!"<< std::endl;
    }
    std::string fragmentString = get_Filestring(fragmentPath);
    if (fragmentString.empty()){
        std::cerr<<"No fragment shader!"<< std::endl;
    }
    
    std::shared_ptr<RenderEngine::ShaderProgramm> newShader =  std::make_shared<RenderEngine::ShaderProgramm>(vertexString,fragmentString);
    if (!newShader->isCompiled()){
        std::cerr<< "Can't load shader program:"<<"\n"
        <<"Vertex: " << vertexPath<< "\n" 
        <<"Fragment: " <<fragmentPath
        <<std::endl;
        return nullptr;
    }
    std::cout<<"shader programm " <<shaderName << " loaded right"<<std::endl;
    return newShader;

}


PrimitiveShader::PrimitiveShader(const std::string path, const std::string relativePath, const glm::ivec2 windsize) : 
                                 ShaderBuffers(path,relativePath,windsize)
{
    std::cout<<"primitive shaderprogramm created"<<std::endl;
}

PrimitiveShader::~PrimitiveShader()
{
}

void PrimitiveShader::createDemoShader(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath)
{
  
    
//     auto pSimpleShaderProgram = _resourcePrimitive->getShaderProgram("freeshader1"); 
    _shadep = loadShaders(shaderName,vertexPath,fragmentPath); 
    _shadep->use();
    _shadep->setVec2("offsete",SIMPLEOFFSET);
     _primitiveInitialized = true;
}

void PrimitiveShader::useDemoShader()
{
            //using pointer to shader
    if(_primitiveInitialized){
    _shadep->use();
    
    glBindVertexArray(_vao_primitive_6vf);
    glDrawArrays(GL_TRIANGLES,0,6);
    }
}

TransformShader::TransformShader(const std::string path, const std::string relativePath, const glm::ivec2 windsize): 
                                 ShaderBuffers(path,relativePath,windsize)
{
    
}

TransformShader::~TransformShader()
{
}


void TransformShader::createDemoShader(const std::string& shaderName,const std::string& vertexPath,const std::string& fragmentPath)
{
   
   _shadet = loadShaders(shaderName,vertexPath,fragmentPath);  
     glm::mat4 projectionMatrix = glm::ortho (0.0f,_fWindsize.x,0.0f,_fWindsize.y,-10.0f,100.0f);
//     _shadet = _resourcePrimitive->getShaderProgram("transshader1"); 
    _shadet->use();
    _shadet->setMatrix4("projectionMat", projectionMatrix);
}


void TransformShader::useDemoShader()
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
    modelMatrix_t00  = glm::rotate(modelMatrix_t00 ,glm::radians(_grades/2),glm::vec3(0.f,0.f,1.f)); 
    modelMatrix_t00   = glm::translate(modelMatrix_t00  ,glm::vec3(.5f,.5f,0.f));
    modelMatrix_t00  = glm::scale(modelMatrix_t00  ,glm::vec3(0.5f,0.5f,.5f));
    _shadet->setMatrix4("modelMat",modelMatrix_t00 );
    glLineWidth(3); 
    glDrawArrays( GL_TRIANGLES,0,6);
    
    glm::mat4 modelMatrix_t01  = glm::mat4(1.0f);

    modelMatrix_t01   = glm::translate(modelMatrix_t01 ,glm::vec3(0.5f*_fWindsize.x,0.5f*_fWindsize.y,0.f));
    modelMatrix_t01   = glm::rotate(modelMatrix_t01  ,glm::radians(_grades),glm::vec3(0.f,0.f,1.f));
    modelMatrix_t01   = glm::translate(modelMatrix_t01 ,glm::vec3(0.5f*size.x,0.5f*size.y,0.f));
    
    modelMatrix_t01  = glm::scale(modelMatrix_t01  ,glm::vec3(100.f,100.f,.05f));
    modelMatrix_t01   = glm::translate(modelMatrix_t01 ,glm::vec3(.3,1.0f,0.f));
    _shadet->setMatrix4("modelMat",modelMatrix_t01 );
    glDrawArrays( GL_LINE_LOOP,0,3);
    glDrawArrays( GL_TRIANGLES,3,3);
    modelMatrix_t01   = glm::rotate(modelMatrix_t01  ,-1.0f*glm::radians(_grades*2),glm::vec3(0.f,0.f,1.f));
    
    _shadet->setMatrix4("modelMat",modelMatrix_t01 );
    glBindVertexArray(_vao_primitive_6vf);
    
    glDrawArrays( GL_LINE_LOOP,0,3);
    glDrawArrays( GL_TRIANGLES,3,3);
    glDrawArrays(GL_LINE,0,6);
}



// void DemoShader::createTransformerShader()
// {
//         _resourcePrimitive = std::make_unique<ResourcePrimitive>(_path,_relativePath);
//     _resourcePrimitive->loadJsonResources();
//     
//         glm::mat4 projectionMatrix = glm::ortho (0.0f,_fWindsize.x,0.0f,_fWindsize.y,-10.0f,100.0f);
//     _shadet = _resourcePrimitive->getShaderProgram("transshader1"); 
//     _shadet->use();
//     _shadet->setMatrix4("projectionMat", projectionMatrix);
// }



