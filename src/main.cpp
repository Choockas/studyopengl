
#include "mainwindow.hpp"
#include "appl.hpp"



GLFWwindow* pStartWindow;
const glm::ivec2 g_windowsize(960,600);



int main(int argc, char** argv)
{

    
    SetWindow startWindow("Start_Window");
    
    if (startWindow.get_result()) {
        startWindow.createWindow(g_windowsize);   
        pStartWindow= startWindow.get_pWindow();        
    } else pStartWindow = nullptr;
    
    
    glfwSetKeyCallback(pStartWindow,glfwKeyCallBack);
    glfwSetWindowSizeCallback(pStartWindow,glfwWindowSizeCallBack);
    startWindow.init();
    
    //brush area for exist
    {
    MyAppl myappl(pStartWindow,g_windowsize);
    // pass directory mame    
    myappl.init(argv[0]);
    myappl.go();
    }

   glfwTerminate();
   
    return 0;
}



