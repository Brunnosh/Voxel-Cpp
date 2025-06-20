#include <application.hpp>


void Application::initWindow(){
    glfwInit();



    m_Window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void Application::mainLoop(){

        while (!glfwWindowShouldClose(m_Window)) {
        glfwPollEvents();
        
    }
    
}
void Application::cleanup(){


    glfwDestroyWindow(m_Window);

    glfwTerminate();
}
