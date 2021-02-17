#include "appl.hpp"
#include "renderer.hpp"

std::array<bool,349> qkeys;


MyAppl::MyAppl(GLFWwindow* pSWindow) : _pwndw(pSWindow) 
{   
}

void MyAppl::go()

{
    
        while (!glfwWindowShouldClose(_pwndw))
        {
            glfwSwapBuffers(_pwndw);
            /* Poll for and process events */
            glfwPollEvents();
        }
}


void MyAppl::init()
{
    std::cout << "Renderer:"<<RenderEngine::Renderer::getRendererStr()<<std::endl;
    std::cout << "Version:"<<RenderEngine::Renderer::getVersionString()<<std::endl;
    std::cout<< "Shader version:"<<RenderEngine::Renderer::getShaderVersionString() <<std::endl;
    RenderEngine::Renderer::setClearColor(0.0,0.3,0.3,1.0);
    RenderEngine::Renderer::clear();      
    glfwSwapBuffers(_pwndw);
    RenderEngine::Renderer::clear();      
}


//     glfwSetKeyCallback(_pFWindow,glfwKeyCallBack);
void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode)
{
    if (key== GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow,GL_TRUE);
    }
   qkeys[key]=action;   
}
