#pragma once

#include "sprite.h"

class Sphere final : public Sprite {
public:
    Sphere();

    void render(int window_width, int window_height) override;

    void init() override;

private:
    int m_stacks = 20;
    int m_sectors = 20;
};
