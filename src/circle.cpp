#include "circle.h"

#ifdef _WIN32
#define _USE_MATH_DEFINES
#include <math.h>
#endif

#include <cmath>

void Circle::render(int window_width, int window_height) {
    Sprite::render(window_width, window_height);
    glBindVertexArray(m_vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertex_nums + 2);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Circle::Circle() {
    init();
}

void Circle::init() {
    const int vertex_length = 7;
    auto *vertices = new float[(m_vertex_nums + 2) * vertex_length];
    auto radian = (float) (2 * M_PI / m_vertex_nums);

    memset(vertices, 0, sizeof(float) * (m_vertex_nums + 2) * vertex_length);

    // 颜色数据
    vertices[3] = 0.5f;
    vertices[4] = 0.5f;
    vertices[5] = 0.0f;
    vertices[6] = 1.0f;

    for (int i = 0; i < m_vertex_nums; i++) {
        vertices[vertex_length * (i + 1)] = (float) sin(radian * i);
        vertices[vertex_length * (i + 1) + 1] = (float) cos(radian * i);
        vertices[vertex_length * (i + 1) + 2] = 0.0f;
        vertices[vertex_length * (i + 1) + 3] = 0.5f;
        vertices[vertex_length * (i + 1) + 4] = 0.5f;
        vertices[vertex_length * (i + 1) + 5] = 0.0f;
        vertices[vertex_length * (i + 1) + 6] = 1.0f;
    }

    vertices[(m_vertex_nums + 1) * vertex_length] = (float) sin(radian * m_vertex_nums);
    vertices[(m_vertex_nums + 1) * vertex_length + 1] = (float) cos(radian * m_vertex_nums);
    vertices[(m_vertex_nums + 1) * vertex_length + 2] = 0.0f;
    vertices[(m_vertex_nums + 1) * vertex_length + 3] = 0.5f;
    vertices[(m_vertex_nums + 1) * vertex_length + 4] = 0.5f;
    vertices[(m_vertex_nums + 1) * vertex_length + 5] = 0.0f;
    vertices[(m_vertex_nums + 1) * vertex_length + 6] = 1.0f;

    // 顶点数组对象
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // 顶点缓冲对象
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, (m_vertex_nums + 2) * vertex_length * sizeof(float), vertices, GL_STATIC_DRAW);

    // 设置顶点属性格式
    // 顶点坐标
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_length * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // 颜色值
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertex_length * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    delete[] vertices;
}
