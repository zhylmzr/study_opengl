#pragma once

#include "sprite.h"
#include "shader.h"

class Circle : public Sprite {
public:
    Circle(float x, float y, float radius);

    void render(int window_width, int window_height) const override;

    void init() override;

private:
    float m_radius;

    int m_vertex_nums = 90;
};