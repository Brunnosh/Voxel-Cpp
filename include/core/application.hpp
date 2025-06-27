#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <log.hpp>
#include <shader.hpp>
#include <renderer.hpp>



class Application
{
private:
    GLFWwindow* m_Window = NULL;
    Renderer m_Renderer;
    uint32_t WIDTH = 1280;
    uint32_t HEIGHT = 720;




    void init();
    void mainLoop();
    void cleanup();


    void menuLoop();

    void singlePlayerInit();
    void singlePlayerLoop();

    void multiPlayerLoop();
    void serverHostLoop();


public:
    void run() {
        init();
        mainLoop();
        cleanup();
    }

};
