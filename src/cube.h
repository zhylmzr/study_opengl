#pragma once
#include "sprite.h"

class Cube final: public Sprite {
public:

    Cube();

    void init() override;

    void render(int window_width, int window_height) override;
};
