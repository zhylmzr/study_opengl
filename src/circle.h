#pragma once

#include "sprite.h"
#include "shader.h"

class Circle final : public Sprite {
public:
    Circle();

    void render(int window_width, int window_height) override;

    void init() override;

private:
    int m_vertex_nums = 45;
};