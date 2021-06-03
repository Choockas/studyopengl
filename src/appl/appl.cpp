#include "renderer.hpp"
#include "resourcemanager.hpp"
#include "menu.hpp"
#include "mouse.hpp"
#include "appl.hpp"
#include <stdio.h>
#define PRIMITIVEOFFSET {0.6f,0.4f}
std::array<bool,349> qkeys;
float aspect;
glm::ivec2 originalWindowSize;
bool menuchange= true; 

MyAppl::MyAppl(GLFWwindow* pSWindow,glm::ivec2 g_size) :           _pwndw(pSWindow), 
_windsize(g_size)
{
  
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
    //set up all for menu
    _rm->managerInit(_path);
    
    //section below used to establishe menu
   _menu= std::make_shared<Menu>(_rm);
    
    auto pSpriteShaderProgram = _rm->getShaderProgram("spriteShader");
    
    if (!pSpriteShaderProgram){
        std::cerr<<"Can't find shader programm " << "spriteShader" <<std::endl;
    }
    glm::mat4 projectionMatrix = glm::ortho (0.0f, static_cast<float>(_windsize.x),0.0f,static_cast<float>( _windsize.y),-0.1f,100.0f);
    pSpriteShaderProgram->use(); 
    pSpriteShaderProgram->setInt("tex",0);
    pSpriteShaderProgram -> setMatrix4("projectionMat", projectionMatrix);
    /*****************************/
    float tverticles[]={
        -0.33f, -0.33f, 0.0f,
         0.33f, -0.33f, 0.0f,
         -0.33f,  0.33f, 0.0f,
        -0.33f,  0.33f, 0.0f,
         0.33f,  0.33f, 0.0f,
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
            actualyAct=1000;
            menuchange= false;
        } 
        
        render();
        switch (_applstate)
        {
            case 1:
                primitive1ShaderUse();
                break;
            case 2:
                primitiveTransformShaderUse();
                break;
            default:
                break;
        }
        glfwSwapBuffers(_pwndw);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glBindVertexArray(0);
    _menu->clear_vecobjects();
}

//simplest using shader, drawing
void MyAppl::primitive1ShaderUse()
{
    //using pointer to shader
    if(_primitiveInitialized){
    _shadep->use();
    
    glBindVertexArray(_vao_primitive_6vf);
    glDrawArrays(GL_TRIANGLES,0,6);
    }
}

void MyAppl::primitiveTransformShaderUse()
{
    _shadet->use();
    glBindVertexArray(_vao_primitive_6vf);
    glDrawArrays(GL_TRIANGLES,0,6);
    
}



void MyAppl::proc100()
{
   glfwSetWindowShouldClose(_pwndw,GL_TRUE);
}

void MyAppl::createPrimitive_6vf()
{
//     auto pSimpleShaderProgram = _rm->getShaderProgram("simpleShader"); 
    _shadep = _rm->getShaderProgram("simpleShader"); 
    _shadep->use();
    _shadep->setVec2("offsete",PRIMITIVEOFFSET);
    _primitiveInitialized = true;
}

void MyAppl::createPrimitiveTransform()
{
    _shadet = _rm->getShaderProgram("transShader"); 
    _shadet->use();
    _shadet->setVec2("offsete",{.0f,.0f});
}




void MyAppl::update(unsigned int menuAct)
{
    
    switch(menuAct)
    {
        case 0:
            break;
        case 1:
            _applstate = 0;
            break;
        case 2: 
            _applstate = 0;
            break;
        case 100:
            proc100();
            break;
        case 101:
            createPrimitive_6vf();
            _applstate=1;
            break;
        case 102:
            createPrimitiveTransform();
            _applstate=2;
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
//         snprintf(titlestring, 50, "Xpos: %lf, Ypos:%lf ", MouseViewPort::get_xpos(),originalWindowSize.y- MouseViewPort::get_ypos());
//         glfwSetWindowTitle(pWindow, titlestring);
//         std::cout<<"xpos="<<xpos<<" ypos="<<ypos<<std::endl;
        menuchange = true;
    };
//     if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
}


