#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"
#include <iostream>
#include <array>
#include "mainwindow.hpp"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include <memory>
#include <vector>
#include <map>


void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow *pWindow, int button, int action, int mods);
void glfwWindowSizeCallBack(GLFWwindow *pWindow, int width, int hight);

class MyAppl{
    
public:
    
    MyAppl(GLFWwindow* pSWindow,glm::ivec2 g_size);
    ~MyAppl();
    void init(const std::string& executablePath);
    void go();
    void render();
    void update(unsigned int menuAct);
    void proc100();
    float get_windsizex(){return _windsize.x;}
    float get_windsizey(){return _windsize.y;}
private:
    float _verticles[9];
     GLFWwindow* _pwndw;
     std::string _path;
     glm::ivec2  _windsize;
     
     
    
};


