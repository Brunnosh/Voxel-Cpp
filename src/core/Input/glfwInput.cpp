#include <application.hpp>
#include <glfwInput.hpp>
#include <appContext.hpp>

void processInput(GLFWwindow * window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        G.camera->processKeyboard(CameraMovement::FORWARD, G.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        G.camera->processKeyboard(CameraMovement::BACKWARD, G.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        G.camera->processKeyboard(CameraMovement::LEFT, G.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        G.camera->processKeyboard(CameraMovement::RIGHT, G.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        G.camera->processKeyboard(CameraMovement::UP, G.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        G.camera->processKeyboard(CameraMovement::DOWN, G.deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        if (!G.camera->escDown) {
            G.camera->menu = !G.camera->menu;
            G.camera->firstMouse = true;
            glfwSetInputMode(window, GLFW_CURSOR, G.camera->menu ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
        }
        G.camera->escDown = true;
    }
    else {
        G.camera->escDown = false;
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        if (!G.camera->lDown) {
            G.camera->wireframe = !G.camera->wireframe;
            glPolygonMode(GL_FRONT_AND_BACK, G.camera->wireframe ? GL_FILL : GL_LINE);
        }
        G.camera->lDown = true;
    }
    else {
        G.camera->lDown = false;
    }

    if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        Application::toggleVSYNC();
    }



}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (!G.camera) return;
    if (G.camera->menu) return;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (G.camera->firstMouse)
    {
        G.camera->camLastX = xpos;
        G.camera->camLastY = ypos;
        G.camera->firstMouse = false;
    }

    float xoffset = xpos - G.camera->camLastX;
    float yoffset = G.camera->camLastY - ypos; // reversed since y-coordinates go from bottom to top

    G.camera->camLastX = xpos;
    G.camera->camLastY = ypos;

    G.camera->processMouseMovement(xoffset, yoffset);
}