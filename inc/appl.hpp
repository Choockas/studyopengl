#pragma once
#include "mainwindow.hpp"
// #include <iostream>
// #include <array>

#include "document.h"
#include "error/en.h"
#include <memory>
#include <vector>
#include <map>




void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow *pWindow, int button, int action, int mods);
void glfwWindowSizeCallBack(GLFWwindow *pWindow, int width, int hight);
class ResourceManager;
class ResourceFinder;
class ResourcePrimitive;
class Menu;
class ShaderBuffers;
class PrimitiveShader;
namespace RenderEngine{
class ShaderProgramm;}




class MyAppl{
    
public:
    
    MyAppl(GLFWwindow* pSWindow,glm::ivec2 g_size);
    ~MyAppl();
    void init(const std::string& executablePath);
    void go();
    void render();
    void update();
private: 

public:
    void contentChanger(const unsigned int menuAct); //implement menu command
    void filePad();
    void on_offPrimitive_6vf(const std::string path, const std::string relativePath,const bool on_off, const glm::ivec2 windsize); // create _vao_primitive_6vf
    void createPrimitiveTransform(const std::string path, const std::string relativePath,const bool on_off, const glm::ivec2 windsize);
    void primitive1ShaderUse();
    void primitiveTransformShaderUse( float grades, float trmod);
    
//     shaderVector get_demoShaders(){ return _demoShaders;}
     
private:
    float _verticles[9];
     GLFWwindow* _pwndw;
     std::string _path;
     const glm::ivec2  _windsize;
     std::shared_ptr<ResourcePrimitive>   _resourcePrimitive; 
     std::unique_ptr<ResourceFinder> _rmfinder;
     std::unique_ptr<PrimitiveShader> _primitiveShader;
     std::unique_ptr<ShaderBuffers> _transformShader;
     std::shared_ptr<Menu> _menu;
//   very simple shader
//      std::shared_ptr<RenderEngine::ShaderProgramm> _shadep;
//  shader that using matrix uniform    
     
     unsigned int _applstate =0;
};


