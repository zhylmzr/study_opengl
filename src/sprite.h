#pragma once

#include "shader.h"

#ifdef _WIN32
#define _USE_MATH_DEFINES
#include <math.h>
#endif
#include <cmath>

#define SAFE_DELETE_BUFFER(buffer)  if(!buffer) glDeleteBuffers(1, &buffer);

class Sprite {
public:

    Sprite();
    ~Sprite();

    virtual void render(int window_width, int window_height);

    void useShader(Shader *shader);

    virtual void init() = 0;

    void setModel(const glm::mat4 &mat);

protected:
    Shader *m_shader;

    glm::mat4 *m_model;
    glm::mat4 *m_view;
    glm::mat4 *m_projection;

    unsigned m_vao{}; // 顶点数组对象
    unsigned m_vbo{}; // 顶点缓冲对象
    unsigned m_ebo{}; // 顶点索引对象
};