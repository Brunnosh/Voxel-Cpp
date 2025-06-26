#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <log.hpp>
#include <shader.hpp>
#include <renderer.hpp>

enum class ApplicationState {
    Menu,
    SinglePlayer,
    MultiPlayer,
    Server,
    Exiting
};

class Application
{
private:
    GLFWwindow* m_Window = NULL;
    Renderer m_Renderer;
    std::unordered_map<shaderType, Shader> m_ShaderMap;
    unsigned int m_ModelLoc;
    uint32_t WIDTH = 1280;
    uint32_t HEIGHT = 720;

    ApplicationState m_AppState = ApplicationState::Menu;


    void init();
    void mainLoop();
    void cleanup();


    void menuLoop();
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
