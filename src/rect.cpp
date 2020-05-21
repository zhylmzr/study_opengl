#include "rect.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

using namespace std;

Rect::Rect(int x, int y, int width, int height) {
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    init();
}

void Rect::init() {
    static float vertices[] = {
            // 位置, 颜色, 纹理
            -1.0f, 1.0f, 0.0f, 1.0f, 0.647f, 0.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 1.0f, 0.647f, 0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 0.647f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0, -1.0f, 0.0f, 1.0f, 0.647f, 0.0f, 1.0f, 1.0f, 0.0f,
    };
    static unsigned int indices[] = {
            0, 1, 2,
            1, 3, 2
    };

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

    // 设置顶点属性格式
    // 顶点坐标
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    // 颜色值
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // 纹理坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *) (7 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Rect::render(int window_width, int window_height) const {
    m_shader->use();
    glm::mat4 transform{1};

    float scale_x = (float) m_width / (float) window_width;
    float scale_y = (float) m_height / (float) window_height;

    float current_x = -scale_x;
    float current_y = scale_y;

    float target_x = (float) m_x / ((float) window_width / 2);
    float target_y = (float) m_y / ((float) window_height / 2);

    transform = glm::translate(transform, glm::vec3(target_x - current_x, target_y - current_y, 0.0f));
    transform = glm::rotate(transform, -(float) glfwGetTime(), glm::vec3(0, 0, 1));
    transform = glm::scale(transform, glm::vec3(scale_x, scale_y, 0));

    m_shader->setMat4("model", transform);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}