#include "appl.hpp"





MyAppl::MyAppl(SetWindow& pSWindow) : _pwndw(pSWindow.get_pWindow()) 
{
   
    
}

void MyAppl::go()
{
    while (!glfwWindowShouldClose(_pwndw))
        {
            /* Render here */
            
            
            glfwSwapBuffers(_pwndw);
            /* Poll for and process events */
            glfwPollEvents();
        }
}


void MyAppl::init()
{
    glClearColor(0.5,0.3,0.1,1.0);
}

