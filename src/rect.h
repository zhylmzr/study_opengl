#pragma once

#include "sprite.h"

class Rect final : public Sprite {
public:
    Rect();

    void render(int window_width, int window_height) override;

    void init() override;
};