#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <log.hpp>

enum class ApplicationState {
    Menu,
    SinglePlayer,
    Server,
    Exiting
};

class Application
{
private:
    GLFWwindow* m_Window = NULL;
    uint32_t WIDTH = 1280;
    uint32_t HEIGHT = 720;

    ApplicationState m_AppState = ApplicationState::Menu;


    void init();
    void mainLoop();
    void cleanup();

    void menuLoop();


public:
    void run() {
        init();
        mainLoop();
        cleanup();
    }

};
