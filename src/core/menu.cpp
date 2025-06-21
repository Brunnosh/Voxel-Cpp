#include <application.hpp>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

void Application::menuLoop() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Main Menu");

    if (ImGui::Button("Single Player")) {
        m_AppState = ApplicationState::SinglePlayer;
        // Inicialize mundo local aqui
    }

    if (ImGui::Button("Host Server")) {
        m_AppState = ApplicationState::Server;
        // Inicialize servidor local aqui
    }

    if (ImGui::Button("Exit")) {
        m_AppState = ApplicationState::Exiting;
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}