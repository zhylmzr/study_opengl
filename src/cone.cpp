#include "cone.h"

Cone::Cone() {
    init();
}

void Cone::init() {
    const int vertex_length = 7;
    auto *vertices = new float[(m_vertex_nums + 2) * vertex_length];
    auto radian = (float) (2 * M_PI / m_vertex_nums);

    memset(vertices, 0, sizeof(float) * (m_vertex_nums + 2) * vertex_length);

    vertices[0] = 0;
    vertices[1] = 1.0f;
    vertices[2] = 0;

    // 颜色数据
    vertices[3] = 0.5f;
    vertices[4] = 0.5f;
    vertices[5] = 0.0f;
    vertices[6] = 1.0f;

    for (int i = 0; i < m_vertex_nums; i++) {
        vertices[vertex_length * (i + 1)] = (float) sin(radian * i);
        vertices[vertex_length * (i + 1) + 1] = -1.0f;
        vertices[vertex_length * (i + 1) + 2] = (float) cos(radian * i);
        vertices[vertex_length * (i + 1) + 3] = 0.5f;
        vertices[vertex_length * (i + 1) + 4] = 0.5f;
        vertices[vertex_length * (i + 1) + 5] = 0.0f;
        vertices[vertex_length * (i + 1) + 6] = 1.0f;
    }

    // 底部中心圆点
    vertices[(m_vertex_nums + 1) * vertex_length] = 0;
    vertices[(m_vertex_nums + 1) * vertex_length + 1] = -1.0f;
    vertices[(m_vertex_nums + 1) * vertex_length + 2] = 0;
    vertices[(m_vertex_nums + 1) * vertex_length + 3] = 0.5f;
    vertices[(m_vertex_nums + 1) * vertex_length + 4] = 0.5f;
    vertices[(m_vertex_nums + 1) * vertex_length + 5] = 0.0f;
    vertices[(m_vertex_nums + 1) * vertex_length + 6] = 1.0f;

    unsigned *indices = new unsigned[m_vertex_nums * 6];
    memset(indices, 0, sizeof(unsigned) * m_vertex_nums * 6);

    // 侧面
    for (int i = 0; i < m_vertex_nums; i++) {
        indices[i * 3] = 0;
        indices[i * 3 + 1] = i + 1;
        if (i == m_vertex_nums - 1) {
            indices[i * 3 + 2] = 1;
        } else {
            indices[i * 3 + 2] = i + 2;
        }
    }

    // 底面
    for (int i = 0; i < m_vertex_nums; i++) {
        indices[3 * m_vertex_nums + i * 3] = m_vertex_nums + 1;
        indices[3 * m_vertex_nums + i * 3 + 1] = i + 1;
        if (i == m_vertex_nums - 1) {
            indices[3 * m_vertex_nums + i * 3 + 2] = 1;
        } else {
            indices[3 * m_vertex_nums + i * 3 + 2] = i + 2;
        }
    }

    // 顶点数组对象
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // 顶点缓冲对象
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, (m_vertex_nums + 2) * vertex_length * sizeof(float), vertices, GL_STATIC_DRAW);

    // 顶点索引缓冲
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertex_nums * 6 * sizeof(unsigned), indices, GL_STATIC_DRAW);

    // 设置顶点属性格式
    // 顶点坐标
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_length * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // 颜色值
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertex_length * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    delete[] vertices;
    delete[] indices;
}

void Cone::render(int window_width, int window_height) {
    Sprite::render(window_width, window_height);
    glBindVertexArray(m_vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, m_vertex_nums * 6, GL_UNSIGNED_INT, nullptr);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
