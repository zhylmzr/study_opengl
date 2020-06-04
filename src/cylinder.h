#pragma once

#include "sprite.h"

class Cylinder final : public Sprite {
public:
    void render(int window_width, int window_height) override;

    void init() override;

    Cylinder();

private:
    int m_vertex_nums = 45;
};

