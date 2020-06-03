#include "cube.h"

Cube::Cube() {
    init();
}

void Cube::init() {
    static float vertices[] = {
            // 位置, 颜色, 纹理
            -1.0f, 1.0f, 1.0f, 1.0f, 0.647f, 0.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, 1.0f, 0.647f, 0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f, 0.647f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0, -1.0f, 1.0f, 1.0f, 0.647f, 0.0f, 1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, -1.0f, 1.0f, 0.647f, 0.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, -1.0f, 1.0f, 0.647f, 0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, -1.0f, 1.0f, 0.647f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0, -1.0f, -1.0f, 1.0f, 0.647f, 0.0f, 1.0f, 1.0f, 0.0f,
    };
    static unsigned int indices[] = {
            0, 1, 2,
            1, 3, 2,
            0, 5, 1,
            4, 5, 0,
            4, 5, 6,
            6, 5, 7,
            2, 3, 7,
            2, 7, 6,
            5, 1, 3,
            5, 3, 7,
            4, 0, 2,
            4, 2, 6
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

void Cube::render(int window_width, int window_height) {
    Sprite::render(window_width, window_height);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}
