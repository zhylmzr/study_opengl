#pragma once

#include "sprite.h"

class Rect : public Sprite {
public:
    Rect(float x, float y, float width, float height);

    void render(int window_width, int window_height) const override;

    void init() override;
};