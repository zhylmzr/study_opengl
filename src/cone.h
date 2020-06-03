#pragma once

#include "sprite.h"

class Cone final : public Sprite {
public:
    Cone();

    void init() override;

    void render(int window_width, int window_height) override;

private:
    int m_vertex_nums = 45;
};
