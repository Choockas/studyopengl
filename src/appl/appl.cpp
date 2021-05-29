#include "renderer.hpp"
#include "resourcemanager.hpp"
// #include "shaderprogramm.hpp"
#include "menu.hpp"
#include "mouse.hpp"
#include "appl.hpp"
#include <stdio.h>

std::array<bool,349> qkeys;
float aspect;
glm::ivec2 originalWindowSize;
bool menuchange= true; 

MyAppl::MyAppl(GLFWwindow* pSWindow,glm::ivec2 g_size) :           _pwndw(pSWindow), 
_windsize(g_size)
{

//     for (int ic=0; ic <9;ic++)_verticles[ic]=tverticles[ic];
  
}

MyAppl::~MyAppl()
{
    
}

void MyAppl::init(const std::string& executablePath)
{
    std::cout << "Renderer:"<<RenderEngine::Renderer::getRendererStr()<<std::endl;
    std::cout << "Version:"<<RenderEngine::Renderer::getVersionString()<<std::endl;
    std::cout<< "Shader version:"<<RenderEngine::Renderer::getShaderVersionString() <<std::endl;
    RenderEngine::Renderer::setClearColor(0.0,0.3,0.3,1.0);
    glfwSetMouseButtonCallback(_pwndw, mouse_button_callback);
//evaluate executablePath    
    size_t found= executablePath.find_last_of("/\\");
    _path = executablePath.substr(0,found);
    
    aspect = 1.f* _windsize.x/_windsize.y;
    originalWindowSize=_windsize;
    MouseViewPort::set_horAspect(1.f);
    MouseViewPort::set_verAspect(1.f);
 
    _rm = std::make_shared<ResourceManager>();
    _rm->managerInit(_path);
   _menu= std::make_shared<Menu>(_rm);
    
    auto pSpriteShaderProgram = _rm->getShaderProgram("spriteShader");
    
    if (!pSpriteShaderProgram){
        std::cerr<<"Can't find shader programm " << "spriteShader" <<std::endl;
    }
    glm::mat4 projectionMatrix = glm::ortho (0.0f, static_cast<float>(_windsize.x),0.0f,static_cast<float>( _windsize.y),-100.0f,100.0f);
    pSpriteShaderProgram->use(); 
    pSpriteShaderProgram->setInt("tex",0);
    pSpriteShaderProgram -> setMatrix4("projectionMat", projectionMatrix);
}

void MyAppl::go()

{
    unsigned int actualyAct = 1000;

    _menu->update(0);
    while (!glfwWindowShouldClose(_pwndw))
    {
        
        RenderEngine::Renderer::clear(); 
        if(menuchange)
        {
            _menu->update(0);
            actualyAct=_menu->get_actualy();
            update(actualyAct);
            
            menuchange= false;
        } 
        
        render();
        if(_applstate==1){
        _shadep->use();
        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES,0,3);    
        }
        
        glfwSwapBuffers(_pwndw);
        /* Poll for and process events */
        glfwPollEvents();
    }
    _menu->clear_vecobjects();
}




void MyAppl::proc100()
{
    for(int ic=0;ic<100;ic++);
}

void MyAppl::proc101()
{
    float tverticles[]={
        -0.5f, -0.5f,0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    GLfloat colors[]={
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f
        
    };
    
//     auto pSimpleShaderProgram = _rm->getShaderProgram("simpleShader"); 
//     std::shared_ptr<RenderEngine::ShaderProgramm> pSimpleShaderProgram = _rm->getShaderProgram("simpleShader"); 
    _shadep = _rm->getShaderProgram("simpleShader"); 
    _points_vbo = 0;
    glGenBuffers(1,&_points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,_points_vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(tverticles),tverticles,GL_STATIC_DRAW);
    
    _colors_vbo = 0;
    glGenBuffers(1,&_colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,_colors_vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);
    
    _vao = 0;
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,_points_vbo);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,_colors_vbo);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,nullptr);

}



void MyAppl::update(unsigned int menuAct)
{
    
    switch(menuAct)
    {
        case 100:
            proc100();
            break;
        case 101:
            proc101();
            _applstate=1;
            break;
        case 102:
//             std::cout<<menuAct<<" ";
            break;
        default:
//             std::cout<<".";
            
            break;
    }
}

void MyAppl::render()
{
      _menu->render(); 
}

void glfwWindowSizeCallBack(GLFWwindow *pWindow, int width, int hight)
{

    const float aspect_ratio = aspect;
    unsigned int viewPortWidth = width;
    unsigned int viewPortHight = hight;
    unsigned int viewPortLeftOffset =0;
    unsigned int viewPortBottomOffset =0;
    float woh;
    woh =1.f*width/hight;
    if (woh >= aspect_ratio){
        viewPortWidth = aspect_ratio * hight;
        
        if (width>viewPortWidth){
        viewPortLeftOffset = (width - viewPortWidth)/2;
            MouseViewPort::set_viewportLeftOffset(viewPortLeftOffset);
        }
        else { std::cout<<"viewPortWidth ="<<viewPortWidth<< "viewPortLeftOffset ="<<viewPortLeftOffset<< std::endl;}
        
    }        
    if (woh < aspect_ratio){
        viewPortHight =   width/aspect_ratio;
        if(hight>viewPortHight){
        viewPortBottomOffset = (hight - viewPortHight)/2;
        MouseViewPort::set_viewporBottomOffset(viewPortBottomOffset);}
        else { std::cout<<" viewPortHight ="<<viewPortHight<<" viewPortBottomOffset ="<<viewPortBottomOffset<<std::endl;}
    }
    RenderEngine::Renderer::setViewPort(viewPortWidth,viewPortHight,viewPortLeftOffset,viewPortBottomOffset);
   
     MouseViewPort::set_horAspect(1.f*originalWindowSize.x/viewPortWidth);
     MouseViewPort::set_verAspect(1.f*originalWindowSize.y/viewPortHight);     
    
}



void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode)
{
    if (key== GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow,GL_TRUE);
    }
   qkeys[key]=action;   
}


void mouse_button_callback(GLFWwindow *pWindow, int button, int action, int mods)
{
    double xpos, ypos;
    char titlestring[50];
    int xsize,ysize;
    
    glfwGetFramebufferSize(pWindow,&xsize,&ysize); 
    
    if (action == GLFW_PRESS)
    { 
        glfwGetCursorPos(pWindow, &xpos, &ypos);
        
        MouseViewPort::set_pos(xpos,ypos); 
        MouseViewPort::set_button(button);
        MouseViewPort::set_used(true);
        snprintf(titlestring, 50, "Xpos: %lf, Ypos:%lf ", MouseViewPort::get_xpos(),originalWindowSize.y- MouseViewPort::get_ypos());
        glfwSetWindowTitle(pWindow, titlestring);
        std::cout<<"xpos="<<xpos<<" ypos="<<ypos<<std::endl;
        
        menuchange = true;
    };
//     if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
}


