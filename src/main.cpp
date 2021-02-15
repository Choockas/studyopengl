
#include "../inc/appl.hpp"
#include "../inc/mainwindow.hpp"


GLFWwindow* pStartWindow;

void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode);
std::array<bool,349> qkeys;

int main(int argc, char** argv)
{

    
    SetWindow startWindow("Start_Window");
    MyAppl myappl(startWindow);
    if (startWindow.get_result()) startWindow.createWindow({640,480});
    if (startWindow.get_result()) {
        pStartWindow= startWindow.get_pWindow();        
    } else pStartWindow = nullptr;
    startWindow.init();

    myappl.init();
    myappl.go();
    
//std::cout << "Renderer:"<<RenderEngine::Renderer::getRendererStr()<<std::endl;
//std::cout << "Version:"<<RenderEngine::Renderer::getVersionString()<<std::endl;
    
   
    glfwTerminate();
   
    return 0;
}


void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode)
{
    if (key== GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow,GL_TRUE);
    }
   qkeys[key]=action;   
}
