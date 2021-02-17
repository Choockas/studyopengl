
#include "../inc/appl.hpp"
#include "../inc/mainwindow.hpp"


GLFWwindow* pStartWindow;




int main(int argc, char** argv)
{

    
    SetWindow startWindow("Start_Window");
    
    if (startWindow.get_result()) startWindow.createWindow({640,480});
    if (startWindow.get_result()) {
        pStartWindow= startWindow.get_pWindow();        
    } else pStartWindow = nullptr;
    MyAppl myappl(pStartWindow);
    glfwSetKeyCallback(pStartWindow,glfwKeyCallBack);
    startWindow.init();
    
    myappl.init();
    myappl.go();

   
    glfwTerminate();
   
    return 0;
}



