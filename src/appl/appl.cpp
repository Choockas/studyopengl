#include "appl.hpp"
#include "renderer.hpp"
#include "resourcemanager.hpp"


std::array<bool,349> qkeys;


MyAppl::MyAppl(GLFWwindow* pSWindow) : _pwndw(pSWindow) 
{   
}

MyAppl::~MyAppl()
{
    
}


void MyAppl::go()

{
        ResourceManager resourceManager;
        resourceManager.managerInit(_path);
    
        while (!glfwWindowShouldClose(_pwndw))
        {
            RenderEngine::Renderer::clear(); 
            glfwSwapBuffers(_pwndw);
            /* Poll for and process events */
            glfwPollEvents();
        }
}


void MyAppl::init(const std::string& executablePath)
{
    std::cout << "Renderer:"<<RenderEngine::Renderer::getRendererStr()<<std::endl;
    std::cout << "Version:"<<RenderEngine::Renderer::getVersionString()<<std::endl;
    std::cout<< "Shader version:"<<RenderEngine::Renderer::getShaderVersionString() <<std::endl;
    RenderEngine::Renderer::setClearColor(0.0,0.3,0.3,1.0);
//evaluate executablePath    
    size_t found= executablePath.find_last_of("/\\");
    _path = executablePath.substr(0,found);     
}


void MyAppl::render()
{
    
}



void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode)
{
    if (key== GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow,GL_TRUE);
    }
   qkeys[key]=action;   
}

