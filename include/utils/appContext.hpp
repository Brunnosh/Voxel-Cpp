#pragma once

#include <cstdint>



enum class ApplicationState {
    Menu,
    SinglePlayer,
    MultiPlayer,
    Server,
    Exiting
};

class AppContext {
private:

public:
    ApplicationState appState = ApplicationState::Menu;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;



    // outros ponteiros globais possíveis
    // Camera* camera = nullptr;
    // World* world = nullptr;
};

extern AppContext G;