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

struct AppContext {

public:
    uint32_t* windowWidthRef;
    uint32_t* windowHeightRef;
    ApplicationState appState = ApplicationState::Menu;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    Camera* camera = NULL;


};

struct Configs
{
    bool VSYNC = false;
    int renderDistance = 8; //Chunks
};

extern Configs cfg;
extern AppContext G;