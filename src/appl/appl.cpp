#include "renderer.hpp"
#include "resourcemanager.hpp"
#include "resourcefinder.hpp"
#include "resourcemenu.hpp"
#include "demoshader.hpp"
#include "framedsprite.hpp"
#include "menu.hpp"
#include "mouse.hpp"
#include "appl.hpp"
#include <stdio.h>


const std::string LOCALPATH = "res/resourcestore.json";
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
    _rmfinder =std::make_unique<ResourceFinder>(_path,LOCALPATH);
    _rmfinder->loadJsonResources();
    std::string trp = _rmfinder->get_resultPath("startmenu");
    //set up all for menu
   _menu= std::make_shared<Menu>(_rmfinder->get_resultPath("startmenu"),_path,_windsize.x,_windsize.y);

   _menu->initMenu();

    
}

void MyAppl::go()

{
    
// it's needed to mirroring ordinate
    _menu->update(_windsize.y);
    
    while (!glfwWindowShouldClose(_pwndw))
    {
        update();
        RenderEngine::Renderer::clear(); 
        render();
 
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
    _primitiveShader->usePrimitiveShader();
}
 
void MyAppl::primitiveTransformShaderUse( float grades, float trmod)
{

    _transformShader->useTransformerShahader(grades);
}



void MyAppl::filePad()
{
   std::string secondRes;
   
}

void MyAppl::on_offPrimitive_6vf(const std::string path, const std::string relativePath,const bool on_off, const glm::ivec2 windsize)
{
    if(on_off){   
    _primitiveShader = std::make_unique<DemoShader>(path,relativePath,windsize);
         _primitiveShader->createPrimitiveShader();
    } else
    {
        _primitiveShader=0;
    }
}




void MyAppl::createPrimitiveTransform(const std::string path, const std::string relativePath,const bool on_off, const glm::ivec2 windsize)
{
        if(on_off){   
    _transformShader = std::make_unique<DemoShader>(path,relativePath,windsize);
         _transformShader->createTransformerShader();
    } else
    {
        _transformShader=0;
    }

}



void MyAppl::contentChanger(const unsigned int menuAct)
{
    
    switch(menuAct)
    {
        case 0:
            break;
        case 1:
            on_offPrimitive_6vf("","", false,_windsize);
//             _menu->set_actbyMenu(101);
            _applstate = 0;
            break;
        case 2: 
            createPrimitiveTransform("","", false,_windsize);
            _applstate = 0;
            break;
        case 100:
            filePad();
            break;
        case 101:
            {
            std::string resPath = _rmfinder->get_resultPath("demofree");
            if(!resPath.empty())
            {
            on_offPrimitive_6vf(_path,resPath, true,_windsize);
            _applstate=1;
            }}
            break;
        case 102:
            {
            std::string resPath = _rmfinder->get_resultPath("demofree");
            if(!resPath.empty())
            {
            createPrimitiveTransform(_path,resPath, true,_windsize);
              _applstate=2;
            }}
            
            break;
        default:
//             std::cout<<".";
            break;
    }
}

void MyAppl::update( )
{
    
        if(menuchange)
        {
//There is it makes change 
            _menu->update(_windsize.y); //check point of tuch 
            const int actMenu=_menu->get_actbyMenu();
            contentChanger(actMenu);
  // on that point make reset                      
            menuchange= false;
        } 
    
}




void MyAppl::render()
{
      _menu->render(); 
        switch (_applstate)
        {
            case 1:
                primitive1ShaderUse();
                break;
            case 2:
                primitiveTransformShaderUse(90.0f,0.0f);
                break;
            default:
                break;
        }
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


