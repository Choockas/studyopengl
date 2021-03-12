#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"
#include <iostream>
#include <array>
#include "mainwindow.hpp"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "memory"
#include <vector>
#include <map>



void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode);

class MyAppl{
    
public:
    
    MyAppl(GLFWwindow* pSWindow);
    ~MyAppl();
    void init(const std::string& executablePath);
    void go();
    void render();

private:
    
     GLFWwindow* _pwndw;
     std::string _path;
     
     
    
};


