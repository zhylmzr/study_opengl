#pragma once

#include "shader.h"

class Sprite {
public:
    virtual void render(int window_width, int window_height) const = 0;

    void use_shader(Shader *shader);

protected:
    Shader *m_shader;
};