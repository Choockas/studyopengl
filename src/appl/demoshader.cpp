#include "demoshader.hpp"
#include "shaderprogramm.hpp"
#include <vector>
#define PRIMITIVEOFFSET {0.6f,0.4f}

DemoShader::DemoShader(const std::string path,const std::string relativePath) : _path(path) , _relativePath(relativePath)
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
    //get data
    glBufferData(GL_ARRAY_BUFFER,sizeof(tverticles),tverticles,GL_STATIC_DRAW);
    
    //set up for 2-d array  (for fragments)
    glGenBuffers(1,&_colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,_colors_vbo);
    //get data
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


void DemoShader::crteateShader()
{
    _resourcePrimitive = std::make_unique<ResourcePrimitive>(_path,_relativePath);
    _resourcePrimitive->loadJsonResources();
    
//     auto pSimpleShaderProgram = _resourcePrimitive->getShaderProgram("freeshader1"); 
    _shadep = _resourcePrimitive->getShaderProgram("freeshader1"); 
    _shadep->use();
    _shadep->setVec2("offsete",PRIMITIVEOFFSET);
     _primitiveInitialized = true;

}

void DemoShader::useShader()
{
        //using pointer to shader
    if(_primitiveInitialized){
    _shadep->use();
    
    glBindVertexArray(_vao_primitive_6vf);
    glDrawArrays(GL_TRIANGLES,0,6);
    }
}

