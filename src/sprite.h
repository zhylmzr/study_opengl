#pragma once

#include "shader.h"

#define SAFE_DELETE_BUFFER(buffer)  if(!buffer) glDeleteBuffers(1, &buffer);

class Sprite {
public:
    virtual void render(int window_width, int window_height) const;

    virtual ~Sprite();

    void use_shader(Shader *shader);

    virtual void init() = 0;

protected:
    Shader *m_shader;

    float m_x, m_y, m_width, m_height;

    unsigned m_vao{}; // 顶点数组对象
    unsigned m_vbo{}; // 顶点缓冲对象
    unsigned m_ebo{}; // 顶点索引对象
};