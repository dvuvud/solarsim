#pragma once

#include "camera.hpp"
#include "../graphics/shader.hpp"

class Renderer {
private:
    Shader shader;
    
public:
    Renderer();
    void init();
    void render(const Camera& camera);
    void cleanup();
    ~Renderer();
};

