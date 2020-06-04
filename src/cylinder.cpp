#include "cylinder.h"

Cylinder::Cylinder() {
    init();
}

void Cylinder::init() {
    // 上下两个面形, 侧面矩形
    // 面形顶点数 m_vertex_nums
    // 总共顶点数 (m_vertex_nums+1) * 2
    const int data_length = 7;
    int vertices_length = (m_vertex_nums + 1) * 2 * data_length;
    auto *vertices = new float[vertices_length];
    auto radian = (float) (2 * M_PI / m_vertex_nums);

    memset(vertices, 0, sizeof(float) * vertices_length);

    // 底部圆心顶点数据
    vertices[0] = 0;
    vertices[1] = -1.0f;
    vertices[2] = 0;
    vertices[3] = 0.5f;
    vertices[4] = 0.5f;
    vertices[5] = 0.0f;
    vertices[6] = 1.0f;

    // 顶部圆心顶点数据
    vertices[vertices_length - data_length] = 0;
    vertices[vertices_length - data_length + 1] = 1.0f;
    vertices[vertices_length - data_length + 2] = 0;
    vertices[vertices_length - data_length + 3] = 0.5f;
    vertices[vertices_length - data_length + 4] = 0.5f;
    vertices[vertices_length - data_length + 5] = 0.0f;
    vertices[vertices_length - data_length + 6] = 1.0f;

    // 底部顶点 1 ～ m_vertex_nums
    // 顶部顶点 m_vertex_nums + 1 ~ m_vertex_nums * 2
    for (int i = 0; i < m_vertex_nums * 2; i++) {
        int c = i % m_vertex_nums;
        vertices[data_length * (i + 1)] = (float) sin(radian * c);
        vertices[data_length * (i + 1) + 1] = i >= m_vertex_nums ? 1.0f : -1.0f;
        vertices[data_length * (i + 1) + 2] = (float) cos(radian * c);
        vertices[data_length * (i + 1) + 3] = 0.5f;
        vertices[data_length * (i + 1) + 4] = 0.5f;
        vertices[data_length * (i + 1) + 5] = 0.0f;
        vertices[data_length * (i + 1) + 6] = 1.0f;
    }

    // 索引顶点数: 上下两圆形+侧面矩形
    // 上下两圆形: m_vertex_nums*3 * 2 (面数*面顶点数 * 上下2个圆形)
    // 侧面矩形: m_vertex_nums*2 * 3(面数 * 面顶点数)
    unsigned *indices = new unsigned[m_vertex_nums * 12];
    memset(indices, 0, sizeof(unsigned) * m_vertex_nums * 12);

    // 侧面
    for (int i = 0; i < m_vertex_nums; i++) {
        // 底三角形
        indices[i * 6] = i + 1;
        indices[i * 6 + 1] = i + 2 > m_vertex_nums ? i + 2 - m_vertex_nums : i + 2;
        indices[i * 6 + 2] = i + 1 + m_vertex_nums;
        // 顶三角形
        indices[i * 6 + 3] = i + 1 + m_vertex_nums;
        indices[i * 6 + 4] =
                i + 1 + m_vertex_nums + 1 > m_vertex_nums * 2 ? i + 1 + m_vertex_nums + 1 - m_vertex_nums : i + 1 +
                                                                                                            m_vertex_nums +
                                                                                                            1;
        indices[i * 6 + 5] = i + 2 > m_vertex_nums ? i + 2 - m_vertex_nums : i + 2;
    }

    // 底面
    for (int i = 0; i < m_vertex_nums; i++) {
        indices[6 * m_vertex_nums + i * 3] = 0;
        indices[6 * m_vertex_nums + i * 3 + 1] = i + 1;
        if (i == m_vertex_nums - 1) {
            indices[6 * m_vertex_nums + i * 3 + 2] = 1;
        } else {
            indices[6 * m_vertex_nums + i * 3 + 2] = i + 2;
        }
    }

    // 顶面
    for (int i = 0; i < m_vertex_nums; i++) {
        indices[9 * m_vertex_nums + i * 3] = m_vertex_nums * 2 + 1;
        indices[9 * m_vertex_nums + i * 3 + 1] = i + 1 + m_vertex_nums;
        if (i == m_vertex_nums - 1) {
            indices[9 * m_vertex_nums + i * 3 + 2] = 1 + m_vertex_nums;
        } else {
            indices[9 * m_vertex_nums + i * 3 + 2] = i + 2 + m_vertex_nums;
        }
    }


    // 顶点数组对象
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // 顶点缓冲对象
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_length * sizeof(float), vertices, GL_STATIC_DRAW);

    // 顶点索引缓冲
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertex_nums * 12 * sizeof(unsigned), indices, GL_STATIC_DRAW);

    // 设置顶点属性格式
    // 顶点坐标
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data_length * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // 颜色值
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, data_length * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    delete[] vertices;
    delete[] indices;
}

void Cylinder::render(int window_width, int window_height) {
    Sprite::render(window_width, window_height);
    glBindVertexArray(m_vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, m_vertex_nums * 12, GL_UNSIGNED_INT, nullptr);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
