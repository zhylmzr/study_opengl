#include "graphic.h"
#include <stb_image.h>
#include <iostream>

using namespace std;

void frame_change_callback(GLFWwindow *pWindow, int width, int height) {
    glViewport(0, 0, width, height);
}

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
    // glfwWindowHint(GLFW_SAMPLES, 4);

    m_pWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_pWindow);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSetFramebufferSizeCallback(m_pWindow, frame_change_callback);

    // glEnable(GL_MULTISAMPLE);

    init_resources();
}

void Graphic::render_start() {
    event_handler();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphic::render_end() const {
    glfwSwapBuffers(m_pWindow);
    glfwPollEvents();
}

void Graphic::render(const Shader& shader) const {
    glBindVertexArray(m_vao);

    shader.setInt("texture2", 1);

    shader.setVec3("uPoint", 0.0f, 0.0f, 0.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_tex0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_tex1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    shader.setVec3("uPoint", 0.5f, 0.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, m_tex1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Graphic::event_handler() {
    if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        ((glfwGetKey(m_pWindow, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS || glfwGetKey(m_pWindow, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS) && glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS)) {
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
    float vertices[] = {
            // 位置, 颜色, 纹理
            -0.5f, .5f, 0.0f,       1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, 0.5f,     0.0f, 0.0f,
            0.5f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f, 0.5f,     1.0f, 1.0f,
            0.5, -0.5f, 0.0f,       1.0f, 0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
    };

    unsigned int indices[] = {
            0, 1, 2,
            1, 3, 2
    };

    // 注意: OpenGL 核心模式要求必须使用VertexArrays, 否则不会进行任何绘制
    // 顶点数组对象
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // 顶点缓冲对象
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 顶点索引缓冲
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7*sizeof(float)));
    glEnableVertexAttribArray(2);

    glEnable(GL_BLEND);
    glGenTextures(1, &m_tex0);
    glBindTexture(GL_TEXTURE_2D, m_tex0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(1);
    int width, height, nrChannels;
    void *data = stbi_load("../resources/image/container.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glGenTextures(1, &m_tex1);
    glBindTexture(GL_TEXTURE_2D, m_tex1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("../resources/image/face.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}