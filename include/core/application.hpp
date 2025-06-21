#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application
{
private:
    GLFWwindow * m_Window;
    uint32_t WIDTH = 1280;
    uint32_t HEIGHT = 720;


    void init();
    void mainLoop();
    void cleanup();
public:
    void run() {
        init();
        mainLoop();
        cleanup();
    }

};
