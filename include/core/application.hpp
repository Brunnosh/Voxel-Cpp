#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <appContext.hpp>
#include <log.hpp>
#include <shader.hpp>
#include <renderer.hpp>



class Application
{
private:
    GLFWwindow* m_Window = NULL;
    Renderer m_Renderer;
    uint32_t m_WindowWidth = 1280;
    uint32_t m_WindowHeight = 720;



    void init();
    void mainLoop();
    void cleanup();


    void menuLoop();

    void singlePlayerInit();
    void singlePlayerLoop();

    void multiPlayerLoop();
    void serverHostLoop();


public:
    static void toggleVSYNC() {
        cfg.VSYNC = !cfg.VSYNC;
        glfwSwapInterval(cfg.VSYNC);
    }
    void run() {
        init();
        mainLoop();
        cleanup();
    }

};
