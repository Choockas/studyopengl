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
class ResourceManager;
class Menu;
namespace RenderEngine{
class ShaderProgramm;}

class MyAppl{
    
public:
    
    MyAppl(GLFWwindow* pSWindow,glm::ivec2 g_size);
    ~MyAppl();
    void init(const std::string& executablePath);
    void go();
    void render();
    void update(unsigned int menuAct);
    void filePad();
    void createPrimitive_6vf(); // create _vao_primitive_6vf
    void createPrimitiveTransform();
    float get_windsizex(){return 0.0f+_windsize.x;}
    float get_windsizey(){return 0.0f+_windsize.y;}
    void primitive1ShaderUse();
    void primitiveTransformShaderUse( float grades, float trmod);
    std::shared_ptr<ResourceManager> get_rm(){return _rm;}
     
private:
    float _verticles[9];
    bool _primitiveInitialized=false;
     GLFWwindow* _pwndw;
     std::string _path;
     glm::ivec2  _windsize;
     typedef std::shared_ptr<ResourceManager>  pResourcesManager;
     GLuint _points_vbo=0;
     GLuint _colors_vbo=0;
     GLuint _vao_primitive_6vf=0;// array for 6 verticles & colorrs layer

     pResourcesManager _rm ;
     std::shared_ptr<Menu> _menu;
//   very simple shader
     std::shared_ptr<RenderEngine::ShaderProgramm> _shadep;
//  shader that using matrix uniform    
     std::shared_ptr<RenderEngine::ShaderProgramm> _shadet;
     unsigned int _applstate =0;
};


