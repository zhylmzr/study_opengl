#include "cube.h"
#include <stb_image.h>

unsigned tex0;

Cube::Cube() {
    init();
}

void Cube::init() {
    static float vertices[] = {
            // 位置, 纹理

            // +z
            -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            // -z
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
            // +y
            -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
            // -y
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
            // +x
            1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
            // -x
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            -1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            -1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
    };

    // 顶点数组对象
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // 顶点缓冲对象
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性格式
    // 顶点坐标
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    // 纹理坐标
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenTextures(1, &tex0);
    glBindTexture(GL_TEXTURE_2D, tex0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(1);
    int width, height, nrChannels;
    void *data = stbi_load("../resources/image/container.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void Cube::render(int window_width, int window_height) {
    Sprite::render(window_width, window_height);

    m_shader->setInt("texture1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex0);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
