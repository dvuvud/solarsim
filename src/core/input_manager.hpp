#pragma once

#include "camera.hpp"
#include "window.hpp"

class InputManager {
private:
    Window* window = nullptr;
    Camera* camera = nullptr;
    
    bool firstMouse = true;
    float lastX = 0.0f;
    float lastY = 0.0f;
    
public:
    void init(Window* window, Camera* camera);
    void processInput(float deltaTime);
    
private:
    void handleMouseMovement(float xpos, float ypos);
    void handleMouseScroll(double xoffset, double yoffset);
    
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};
