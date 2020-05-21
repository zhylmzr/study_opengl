#pragma once

#include "sprite.h"

class Rect : public Sprite {
public:
    Rect(int x, int y, int width, int height);

    void render(int window_width, int window_height) const override;

    void init();

private:
    int m_x, m_y, m_width, m_height;

    unsigned m_vao{}; // 顶点数组对象
    unsigned m_vbo{}; // 顶点缓冲对象
    unsigned m_ebo{}; // 顶点索引对象
};