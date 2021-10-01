#pragma once
#include "mainwindow.hpp"

#include "document.h"
#include "error/en.h"
#include <memory>
#include <vector>
#include <map>




void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow *pWindow, int button, int action, int mods);
void glfwWindowSizeCallBack(GLFWwindow *pWindow, int width, int hight);
class ResourceSprite;
class ResourceFinder;
class ResourcePrimitive;
class Menu;
class ShaderBuffers;
class PrimitiveShader;
class TransformShader;
class SpriteThings;
namespace RenderEngine{
class ShaderProgramm;
class Sprite;
class AnimateSprite;
}




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
    void primitive1ShaderUse() const;
    void primitiveTransformShaderUse( float grades, float trmod) const ;
    bool createSimplestSprite(const std::string demoName);
    bool createAnimatedSprite(const std::string anyName);
    void simplestSpriteRender(const std::string name) const;
    void animateSpriteRender(const glm::ivec2,const glm::ivec2,float) const;
//     shaderVector get_demoShaders(){ return _demoShaders;}
     
private:
    float _verticles[9];
     GLFWwindow* _pwndw;
     std::string _execpath;
     const glm::ivec2  _windsize;
     std::shared_ptr<ResourcePrimitive>   _resourcePrimitive; 
     std::shared_ptr<ResourceSprite> _resourceSprite; 
     std::unique_ptr<ResourceFinder> _rmfinder;
     std::unique_ptr<PrimitiveShader> _primitiveShader;
     std::unique_ptr<TransformShader> _transformShader;
     std::shared_ptr<SpriteThings> _spriteThings;
     std::shared_ptr<Menu> _menu;
     std::shared_ptr<RenderEngine::AnimateSprite> _animsprite = nullptr;
     
     unsigned int _applstate =0;
};


