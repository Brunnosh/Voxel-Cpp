#pragma once

#include <cstdint>
#include <camera.hpp>

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
    Camera* camera = NULL;


};

struct Configs
{
    bool VSYNC = false;
};

extern Configs cfg;
extern AppContext G;