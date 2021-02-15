#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"
#include <iostream>
#include <array>
#include "mainwindow.hpp"



class MyAppl{
    
public:
    
    MyAppl(SetWindow& pSWindow);
    void init();
    void go();
private:
     
     GLFWwindow* _pwndw;
     
     
    
};


