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

    void render_start();

    void render_end() const;

    void render() const;

    void add_obj(Sprite *sprite, Shader *shader);

    bool termination() const;

    void release();

private:
    std::string m_title;
    int m_width;
    int m_height;
    GLFWwindow *m_pWindow{};

    std::vector<Sprite *> m_sprites;

    void init_resources();

    void event_handler();
};
