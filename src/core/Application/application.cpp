#include <application.hpp>
#include <appContext.hpp>
#include <glfwInput.hpp>

#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);


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
    glfwSetWindowUserPointer(m_Window, this);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
    glfwSetKeyCallback(m_Window, key_callback);
    glfwSetCursorPosCallback(m_Window, mouse_callback);
    glfwSwapInterval(cfg.VSYNC);


    //glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    e_Shaders[shaderType::MAIN] = Shader("resources/shaders/mainShaderVertex.glsl", "resources/shaders/mainShaderFragment.glsl");

}

void Application::mainLoop(){
    ApplicationState m_LastAppState = G.appState;

    while (!glfwWindowShouldClose(m_Window)&& G.appState != ApplicationState::Exiting) {


        float currentFrame = static_cast<float>(glfwGetTime());
        G.deltaTime = currentFrame - G.lastFrame;
        G.lastFrame = currentFrame;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5, 0.55, 0.70, 0);
        
        // Detecta mudança de estado
        if (G.appState != m_LastAppState) {
            switch (G.appState) {
            case ApplicationState::Menu:
                //onEnterMenu();
                break;
            case ApplicationState::SinglePlayer:
                singlePlayerInit();
                break;
            case ApplicationState::MultiPlayer:
                //onEnterMultiPlayer();
                break;
            case ApplicationState::Server:
                //onEnterServer();
                break;
            default:
                break;
            }
            m_LastAppState = G.appState;
        }

        // Loop principal por estado
        switch (G.appState) {
        case ApplicationState::Menu:
            menuLoop();
            break;
        case ApplicationState::SinglePlayer:
            singlePlayerLoop();
            break;
        case ApplicationState::MultiPlayer:
            multiPlayerLoop();
            break;
        case ApplicationState::Server:
            serverHostLoop();
            break;
        default:
            break;
        }


        ImGui::Begin("App Metrics");
        ImGui::Text("Frame Time: %.2f ms", G.deltaTime * 1000.0f);
        ImGui::Text("FPS: %.1f", 1.0f / G.deltaTime);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
        
    }
    
}
void Application::cleanup(){


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
