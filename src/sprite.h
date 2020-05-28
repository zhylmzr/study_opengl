#pragma once

#include "shader.h"

#define SAFE_DELETE_BUFFER(buffer)  if(!buffer) glDeleteBuffers(1, &buffer);

class Sprite {
public:
    virtual void render(int window_width, int window_height) const;

    virtual ~Sprite();

    void use_shader(Shader *shader);

    virtual void init() = 0;

    void setCenter(float x, float y, float z);

protected:
    Shader *m_shader;

    glm::vec2 m_position{};                 // 位置
    glm::vec2 m_center{0.5, 0.5};    // 中心点比例
    glm::vec2 m_size{};                     // 大小

    unsigned m_vao{}; // 顶点数组对象
    unsigned m_vbo{}; // 顶点缓冲对象
    unsigned m_ebo{}; // 顶点索引对象
};