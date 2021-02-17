#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"
#include <array>



// void glfwWindowSizeCallBack(GLFWwindow*, int, int);
void framebuffer_size_callback(GLFWwindow*, int, int);



class SetWindow{
public:
    SetWindow(const char* in_name);
    ~SetWindow();
    void createWindow(const glm::ivec2 in_wsize);
    GLFWwindow* get_pWindow()  {return _pFWindow;}
    void setWinSize(int in_x, int in_y){_wsize.x=in_x;_wsize.y=in_y;}
    void init();
    bool get_result() const {return _result;} 
    
//     friend void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode);
private:
    glm::ivec2 _wsize;
    GLFWwindow* _pFWindow;
    const char* _wname;
    bool _result = false;
     
    
};


