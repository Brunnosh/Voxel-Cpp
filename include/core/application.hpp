#pragma once
#include <GLFW/glfw3.h>

class Application
{
private:
    GLFWwindow * m_Window;
    uint32_t WIDTH = 1280;
    uint32_t HEIGHT = 720;


    void initWindow();
    void mainLoop();
    void cleanup();
public:
    void run() {
        initWindow();
        mainLoop();
        cleanup();
    }

};
