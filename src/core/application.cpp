#include <application.hpp>
#include <iostream>


void Application::init(){
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    m_Window = glfwCreateWindow(WIDTH, HEIGHT, "VoxelGame", nullptr, nullptr);
    if (!m_Window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Application::mainLoop(){

    while (!glfwWindowShouldClose(m_Window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
    
}
void Application::cleanup(){


    glfwDestroyWindow(m_Window);

    glfwTerminate();
}
