#pragma once
#include "shader.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Graphic {
public:
    Graphic(const std::string& title, int width, int height);

    void init();
    void render_start();
    void render_end() const;
    void render(const Shader& shader) const;
    bool termination() const;

    void release();
private:
    std::string m_title;
    int m_width;
    int m_height;
    GLFWwindow* m_pWindow{};

    unsigned m_vao{}; // 顶点数组对象
    unsigned m_vbo{}; // 顶点缓冲对象
    unsigned m_ebo{}; // 顶点索引对象

    unsigned m_tex0{};    // 纹理1
    unsigned m_tex1{};    // 纹理2

    void init_resources();

    void event_handler();
};
