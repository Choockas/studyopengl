#include "renderer.hpp"
#include "resourcesprite.hpp"
#include "resourcefinder.hpp"
#include "resourcemenu.hpp"
#include "resourceprimitive.hpp"
#include "demoshader.hpp"
#include "framedsprite.hpp"
#include "spritethings.hpp"
#include "menu.hpp"
#include "mouse.hpp"
#include "appl.hpp"
#include <stdio.h>


const std::string LOCALPATH = "res/resourcestore.json";
std::array<bool,349> qkeys;
float aspect; // windows ratio
glm::ivec2 originalWindowSize;
bool menuchange= true; 



MyAppl::MyAppl(GLFWwindow* pSWindow,glm::ivec2 g_size) :           _pwndw(pSWindow), 
_windsize(g_size)
{
  
}

MyAppl::~MyAppl()
{
    
}

void MyAppl::init(const std::string& executablePath)
{
    std::cout << "Renderer:"<<RenderEngine::Renderer::getRendererStr()<<std::endl;
    std::cout << "Version:"<<RenderEngine::Renderer::getVersionString()<<std::endl;
    std::cout<< "Shader version:"<<RenderEngine::Renderer::getShaderVersionString() <<std::endl;
    RenderEngine::Renderer::setClearColor(0.0,0.3,0.3,1.0);
    glfwSetMouseButtonCallback(_pwndw, mouse_button_callback);
    //evaluate executablePath    
    size_t found= executablePath.find_last_of("/\\");
    _execpath = executablePath.substr(0,found);
    
    aspect = 1.f* _windsize.x/_windsize.y; // windows ratio
    originalWindowSize=_windsize;
    MouseViewPort::set_horAspect(1.f);
    MouseViewPort::set_verAspect(1.f);
    _rmfinder =std::make_unique<ResourceFinder>(_execpath,LOCALPATH);
    _rmfinder->loadJsonResources();
    std::string trp = _rmfinder->get_resultPath("startmenu");
    
    //set up all for menu
    _menu= std::make_shared<Menu>(_rmfinder->get_resultPath("startmenu"),_execpath,_windsize.x,_windsize.y);
    _menu->initMenu();
    //preparing for primitive shader programm
    _resourcePrimitive = std::make_shared<ResourcePrimitive>(_execpath, _rmfinder->get_resultPath("demofree")); 
    _resourcePrimitive->loadJsonResources();
    //preparing for sprites
    _resourceSprite = std::make_shared<ResourceSprite>(_execpath, _rmfinder->get_resultPath("demosprites"));
    _resourceSprite->loadJsonResources();
}



// main loop of aplication
void MyAppl::go()
{
    
// it's needed to mirroring ordinate
    _menu->update(_windsize.y);
    
    while (!glfwWindowShouldClose(_pwndw))
    {
        update();
        RenderEngine::Renderer::clear(); 
        render();
 
        glfwSwapBuffers(_pwndw);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glBindVertexArray(0);
    _menu->clear_vecobjects();
}

//call simplest using shader, drawing
void MyAppl::primitive1ShaderUse() const
{
     _primitiveShader->useDemoShader();
}

//call primitive transform shader
void MyAppl::primitiveTransformShaderUse( float grades, float trmod) const
{

    _transformShader->useDemoShader();
    _transformShader->set_grades(grades);
    _transformShader->chageTrMode(trmod); //just dummy
    
}



void MyAppl::filePad()
{
    //for future development
   std::string secondRes;
}


template<typename T> std::shared_ptr<T> MyAppl::createPrimitive(const std::string path, const std::string relativePath, const glm::ivec2 windsize, const uint8_t shcase, std::shared_ptr<T> t)
{
    // shcase  - number in vector of a pointer to shaderprogram
    const std::string  namePS = _resourcePrimitive->getNameSPstring(shcase);
    const std::string  nameVertex = path+_resourcePrimitive->getNameVertexstring(shcase);
    const std::string nameFragment = path+_resourcePrimitive->getNameFragmentstring(shcase);
    std::shared_ptr<T>  m = std::make_shared<T>(path,relativePath,windsize);
    m->createDemoShader(namePS,nameVertex,nameFragment);    
    return m;
}


bool MyAppl::createSimplestSprite(const std::string demoName)
{
    
    std::string  shaderName;
    std::string initialTextName;
    std::string textureAtlas;    
    bool result = false;
    // first getting names of resourses wich needed for the sprite building
    if(_resourceSprite->get_spriteDate(demoName,shaderName,textureAtlas, initialTextName )){ 
        const std::pair<std::string, std::string> pShaderProgram = _resourceSprite->get_shaderDate(shaderName);     
        // parameters of loadShaders ( nameShaderProgramm, vertex, fragment)
      result= _spriteThings->loadShaders(shaderName,pShaderProgram.first,pShaderProgram.second);
      
      
    // becouse choised shader programm (vsprite.txt) has variable projectionMat it shou'd be initialised !
    auto pSpriteShaderProgram = _spriteThings->getShaderProgram(shaderName);
    glm::mat4 projectionMatrix = glm::ortho (0.0f, 900.0f,0.0f,600.f,-0.1f,100.0f);
    pSpriteShaderProgram->use(); 
    pSpriteShaderProgram->setInt("tex",0);
    pSpriteShaderProgram -> setMatrix4("projectionMat", projectionMatrix);
    
    const std::pair<std::string, std::string> pPath=_resourceSprite->get_textureDate(textureAtlas);
        // parameters of loadTextures (resourcePath, const std::string& textureName,texturePath)
     if(result) result = _spriteThings->loadTextures(pPath.first,textureAtlas,pPath.second);
     else std::cerr<< "shader isn't loaded for "<<textureAtlas<<std::endl;   
     if(result) _spriteThings->loadSprites(demoName, textureAtlas, shaderName, initialTextName);
     else std::cerr<< "texture isn't loaded for "<<demoName<< std::endl;
    }
    return result;
}

bool MyAppl::createAnimatedSprite(const std::string anyName)
{
    std::string  shaderName;
    std::string initialTextName;
    std::string textureAtlas;   
    std::string stateName;
    std::map<std::string,std::vector<std::pair<std::string,uint64_t >>> anidate;
    std::vector<std::pair<std::string,uint64_t>> subTexturesDuration;
    const std::vector<std::pair<std::string,uint64_t>> danstat;
    bool result = false;
    if(_resourceSprite->get_spriteDate(anyName,shaderName,textureAtlas, initialTextName )){ 
        const std::pair<std::string, std::string> pShaderProgram = _resourceSprite->get_shaderDate(shaderName);     
        // parameters of loadShaders ( nameShaderProgramm, vertex, fragment)
        result= _spriteThings->loadShaders(shaderName,pShaderProgram.first,pShaderProgram.second);
        // becouse choised shader programm (vsprite.txt) has variable projectionMat it shou'd be initialised !
        auto pSpriteShaderProgram = _spriteThings->getShaderProgram(shaderName);
        glm::mat4 projectionMatrix = glm::ortho (0.0f, 900.0f,0.0f,600.f,-0.1f,100.0f);
        pSpriteShaderProgram->use(); 
        pSpriteShaderProgram->setInt("tex",0);
        pSpriteShaderProgram -> setMatrix4("projectionMat", projectionMatrix);
        
        const std::pair<std::string, std::string> pPath=_resourceSprite->get_textureDate(textureAtlas);
        if(result) result = _spriteThings->loadTextures(pPath.first,textureAtlas,pPath.second);
        else std::cerr<< "shader isn't loaded for "<<textureAtlas<<std::endl;  
        const std::vector<std::string>  subTextures = _resourceSprite->get_subTextures(textureAtlas);
        
        result=( _spriteThings->loadTextureAtlas(textureAtlas,move(subTextures) ,120,157)!=nullptr);      
        if(result)result = _resourceSprite->get_aniDate(anyName,anidate);
        else std::cerr<<"Can't find date for anisprite"<<std::endl;
        
        if(result)result = _spriteThings->loadAnimateSprites(anyName,textureAtlas,shaderName,initialTextName,anidate);
        else std::cerr<<"Can't load anisprite"<<std::endl;
        if(result){ 
            result = _spriteThings->setCurrentAnimateSprites(anyName);
        }
    }
    
    return result;
}

//draw animatesprite
void MyAppl::animateSpriteRender(const glm::ivec2 position,const glm::ivec2 size, float rotation) const
{

    _spriteThings->renderCurrentAnimationSprite(position,size,rotation);
    
}

// draw simplest sprite
void MyAppl::simplestSpriteRender(const std::string name) const
{
    _spriteThings->getSprites(name)->render({200,300},{128,128},0);
}



/*
*     There's like menu message traslation
*/
void MyAppl::contentChanger(const unsigned int menuAct)
{
    bool result=false;
    _applstate = 0;
    switch(menuAct)
    {
        case 0:
            break;
        case 1:
            _primitiveShader = 0;           
            _menu->set_actbyMenu(0);
            break;
        case 2: 
            _transformShader = 0;
            break;
        case 3: 
            _spriteThings.use_count(); 
            _spriteThings = nullptr;
            
            _menu->set_actbyMenu(0);
            break;
        case 4: 
            _spriteThings.use_count(); 
            _spriteThings = nullptr;
            
            _menu->set_actbyMenu(0);
            break;        
        case 100:
            filePad();
            break;
        case 101:
        {
            /*
             * List of shaders in jsonfile
             * "freeshader1" - 0
             * "transshader1" - 1
             */
            
            std::string resPath = _rmfinder->get_resultPath("demofree");
            if(!resPath.empty())
            {
                _primitiveShader = createPrimitive(_execpath,resPath,_windsize, 0,_primitiveShader);
                _applstate=1;
            }}
            _menu->set_actbyMenu(0);
            break;
        case 102: 
        {
            std::string resPath = _rmfinder->get_resultPath("demofree");
            if(!resPath.empty())
            {
                _transformShader = createPrimitive(_execpath,resPath,_windsize, 1,_transformShader);
                _applstate=2;
            }}
            _menu->set_actbyMenu(0);
            break;
        case 103:
        {
            
            std::string resPath = _rmfinder->get_resultPath("demosprites");
            if(!resPath.empty())
            {              
                if(!_spriteThings) _spriteThings= std::make_shared<SpriteThings>(_execpath,resPath);
                result = createSimplestSprite("falkon");
                if(result)simplestSpriteRender("falkon");else std::cerr<< " sprite isn't loaded"<<std::endl;
                glfwSwapBuffers(_pwndw);
                
                _applstate=3; 
            }
        }
        _menu->set_actbyMenu(0);
        result=false;
        break;
        case 104:
        {
            std::string resPath = _rmfinder->get_resultPath("demosprites");
            if (!resPath.empty()){
                if(!_spriteThings)_spriteThings= std::make_shared<SpriteThings>(_execpath,resPath);
                result = createAnimatedSprite("birdsAnimateSprite");
                if(result)animateSpriteRender({100,300},{120,157},0);else std::cerr<< " sprite isn't loaded"<<std::endl;
                glfwSwapBuffers(_pwndw);
                _applstate=4 ;
            }
        }
        _menu->set_actbyMenu(0);
        result=false;
        break;
        
        default:
            break;
    }
}



// busines in main loop
void MyAppl::update( )
{
    switch (_applstate)
    {
        case 4:
            _spriteThings->updateCurrentAnimateSprite(100000000);
            break;
        default: break;
    }
    
        if(menuchange)
        {
//There is  change maker 
            _menu->update(_windsize.y); //check point of tuch 
            const int actMenu=_menu->get_actbyMenu();
            contentChanger(actMenu);
// flag off                     
            menuchange= false;
        } 
        
    
}


// such as windows rendering
void MyAppl::render()
{
     
        switch (_applstate)
        {
            case 1:
                primitive1ShaderUse();
                break;
            case 2:
                primitiveTransformShaderUse(90.0f,0.0f);
                break;
            case 3:
                simplestSpriteRender("falkon");
                break;
            case 4 :
                animateSpriteRender({100,300},{120,157},0.f);
                break;
            default:
                break;
        }
         _menu->render(); 
}


void glfwWindowSizeCallBack(GLFWwindow *pWindow, int width, int hight)
{
    
    const float aspect_ratio = aspect;
    unsigned int viewPortWidth = width;
    unsigned int viewPortHight = hight;
    unsigned int viewPortLeftOffset =0;
    unsigned int viewPortBottomOffset =0;
    float woh;
    woh =1.f*width/hight;
    
    // define viewport along windows size
    if (woh >= aspect_ratio){
        viewPortWidth = aspect_ratio * hight;
        
        if (width>viewPortWidth){
            viewPortLeftOffset = (width - viewPortWidth)/2;
            MouseViewPort::set_viewportLeftOffset(viewPortLeftOffset);
        }
    }        
    if (woh < aspect_ratio){
        viewPortHight =   width/aspect_ratio;
        if(hight>viewPortHight){
            viewPortBottomOffset = (hight - viewPortHight)/2;
            MouseViewPort::set_viewporBottomOffset(viewPortBottomOffset);}
    }
    RenderEngine::Renderer::setViewPort(viewPortWidth,viewPortHight,viewPortLeftOffset,viewPortBottomOffset);
    
    MouseViewPort::set_horAspect(1.f*originalWindowSize.x/viewPortWidth);
    MouseViewPort::set_verAspect(1.f*originalWindowSize.y/viewPortHight);     
}


void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode)
{
    bool tmode;
    if (key== GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow,GL_TRUE);
    }
   qkeys[key]=action;   
   scancode = 39;
   //for future
   tmode = mode==1? true : false;
}



void mouse_button_callback(GLFWwindow *pWindow, int button, int action, int mods)
{
    bool tmode;
    double xpos, ypos;
/*
 *There expose in title if it needed   
 * char titlestring[50];
    int xsize,ysize;
    glfwGetFramebufferSize(pWindow,&xsize,&ysize); 
*/  
    //read mouse status in window    
    if (action == GLFW_PRESS)
    { 
        glfwGetCursorPos(pWindow, &xpos, &ypos);
        MouseViewPort::set_pos(xpos,ypos); 
        MouseViewPort::set_button(button);
        MouseViewPort::set_used(true);
        menuchange = true;
    };
    //for future
  tmode = mods==1? true : false;
}


