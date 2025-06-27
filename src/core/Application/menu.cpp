#include <application.hpp>
#include <appContext.hpp>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

void Application::menuLoop() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Main Menu");

    if (ImGui::Button("Single Player")) {
        G.appState = ApplicationState::SinglePlayer;
        // Inicialize mundo local aqui
    }

    if (ImGui::Button("Join Server")) {
        G.appState = ApplicationState::MultiPlayer;
        // Inicialize servidor local aqui
    }

    if (ImGui::Button("Host Server")) {
        G.appState = ApplicationState::Server;
        // Inicialize servidor local aqui
    }

    if (ImGui::Button("Exit")) {
        G.appState = ApplicationState::Exiting;
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}