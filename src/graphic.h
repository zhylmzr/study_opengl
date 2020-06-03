#pragma once

#include "shader.h"
#include "sprite.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Graphic {
public:
    Graphic(const std::string &title, int width, int height);

    void init();

    void renderStart();

    void renderEnd() const;

    void render();

    void addSprite(Sprite *sprite, Shader *shader);

    bool termination() const;

    void release();

    GLFWwindow *getWindow() const;

private:
    std::string m_title;
    int m_width;
    int m_height;
    GLFWwindow *m_pWindow{};

    std::vector<Sprite *> m_sprites;

    void init_resources();

    void event_handler();
};
