#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"
#include <iostream>
#include <array>
#include "mainwindow.hpp"

void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode);

class MyAppl{
    
public:
    
    MyAppl(GLFWwindow* pSWindow);
    void init();
    void go();
    
private:
     
     GLFWwindow* _pwndw;
     
     
    
};


