#include "sphere.h"
#include <vector>

using namespace std;

unsigned indices_num;

Sphere::Sphere() {
    init();
}

void Sphere::init() {
    // ref: http://www.songho.ca/opengl/gl_sphere.html
    vector<float> vertices;
    float stacks_step = M_PI / m_stacks;
    float sectors_step = 2 * M_PI / m_sectors;

    float radius = 1.0f;
    float stacks_angle, sectors_angle;
    // 纬度上同样如此
    for (int i = 0; i <= m_stacks; i++) {
        stacks_angle = M_PI / 2 - stacks_step * i;
        float xy = radius * cosf(stacks_angle);
        float z = radius * sinf(stacks_angle);

        // 扇区和顶点的关系是: 顶点数 = 扇区数 + 1
        // 故而需要 <=
        for (int j = 0; j <= m_sectors; j++) {
            sectors_angle = j * sectors_step;
            float x = xy * cosf(sectors_angle);
            float y = xy * sinf(sectors_angle);

            // 顶点坐标
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // 颜色值
            vertices.push_back(0.5f);
            vertices.push_back(0.5f);
            vertices.push_back(0);
            vertices.push_back(1.0f);
        }
    }

    vector<unsigned> indices;
    for (int i = 0; i < m_stacks; i++) {
        unsigned k1 = i * (m_sectors + 1);
        unsigned k2 = k1 + m_sectors + 1;
        for (int j = 0; j < m_sectors; j++, k1++, k2++) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (i != m_stacks - 1) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    indices_num = indices.size();

    // 顶点数组对象
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // 顶点缓冲对象
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // 顶点索引缓冲
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);

    // 设置顶点属性格式
    // 顶点坐标
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // 颜色值
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Sphere::render(int window_width, int window_height) {
    Sprite::render(window_width, window_height);
    glBindVertexArray(m_vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, indices_num, GL_UNSIGNED_INT, nullptr);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
