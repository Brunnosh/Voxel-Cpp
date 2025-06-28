#pragma once

#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

void processInput(GLFWwindow* window);