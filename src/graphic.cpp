#include "graphic.h"
#include <iostream>

using namespace std;

Graphic::Graphic(const string &title, int width, int height) {
    m_title = title;
    m_width = width;
    m_height = height;
}

void Graphic::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//     glfwWindowHint(GLFW_SAMPLES, 4);

    m_pWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_pWindow);
    gladLoadGL();
//     glEnable(GL_MULTISAMPLE);

    init_resources();
}

void Graphic::render_start() {
    int display_w, display_h;
    glfwGetFramebufferSize(m_pWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    event_handler();
}

void Graphic::render_end() const {
    glfwSwapBuffers(m_pWindow);
    glfwPollEvents();
}

void Graphic::render() const {
    for (auto &obj : m_sprites) {
        obj->render(m_width, m_height);
    }
//    glBindVertexArray(m_vao);
//
//    shader.setInt("texture2", 1);
//
//    shader.setVec3("uPoint", 0.0f, 0.0f, 0.0f);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, m_tex0);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, m_tex1);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//    shader.setVec3("uPoint", 0.5f, 0.0f, 0.0f);
//    glBindTexture(GL_TEXTURE_2D, m_tex1);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Graphic::add_obj(Sprite *sprite, Shader *shader) {
    sprite->use_shader(shader);
    m_sprites.push_back(sprite);
}

void Graphic::event_handler() {
    if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        ((glfwGetKey(m_pWindow, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS ||
          glfwGetKey(m_pWindow, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS) &&
         glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS)) {
        glfwSetWindowShouldClose(m_pWindow, 1);
        return;
    }
}

bool Graphic::termination() const {
    return glfwWindowShouldClose(m_pWindow);
}

void Graphic::release() {
    glfwTerminate();
}

void Graphic::init_resources() {
    glEnable(GL_BLEND);
//    glGenTextures(1, &m_tex0);
//    glBindTexture(GL_TEXTURE_2D, m_tex0);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    stbi_set_flip_vertically_on_load(1);
//    int width, height, nrChannels;
//    void *data = stbi_load("../resources/image/container.jpg", &width, &height, &nrChannels, 0);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    stbi_image_free(data);
//
//    glGenTextures(1, &m_tex1);
//    glBindTexture(GL_TEXTURE_2D, m_tex1);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    data = stbi_load("../resources/image/face.png", &width, &height, &nrChannels, 0);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    stbi_image_free(data);
}

GLFWwindow *Graphic::getWindow() const {
    return m_pWindow;
}
