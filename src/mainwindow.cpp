#include "mainwindow.hpp"
#include "glm/vec2.hpp"
#include <iostream>



SetWindow::SetWindow(const char* in_name) : _wname(in_name) 
{
      if (!glfwInit())
    {
        std::cout<<"glfwInid failed"<<std::endl;
        _result= false;
    }
    else _result = true;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
}

SetWindow::~SetWindow()
{
    
}


void SetWindow::createWindow(const glm::ivec2 in_wsize)
{
    _wsize = in_wsize;
    _pFWindow = glfwCreateWindow(_wsize.x, _wsize.y, _wname, nullptr, nullptr);
    if (!_pFWindow)
    {
        std::cout<<"Can't create GLFW window"<<std::endl;
        
        _result = false;
    }
    _result= true;
}



void SetWindow::init()
{
    glfwSetFramebufferSizeCallback(_pFWindow, framebuffer_size_callback);
    glfwMakeContextCurrent(_pFWindow);
    glfwSwapInterval(1);
    if(!gladLoadGL()){
        std::cout<<"Cant Load GLAD"<<std::endl;
        glfwTerminate();
        _result= false;
    }
    _result = true;
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


