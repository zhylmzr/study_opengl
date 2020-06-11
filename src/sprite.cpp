#include "sprite.h"
#include <glm/glm.hpp>

Sprite::Sprite() {
    m_shader = nullptr;

    // 默认没有单独的视图和投影矩阵
    m_view = nullptr;
    m_projection = nullptr;
    m_model = new glm::mat4;
}

void Sprite::useShader(Shader *shader) {
    m_shader = shader;
}

Sprite::~Sprite() {
    SAFE_DELETE_BUFFER(m_vao)
    SAFE_DELETE_BUFFER(m_vbo)
    SAFE_DELETE_BUFFER(m_vbo)

    delete m_view;
    delete m_projection;
    delete m_model;
}

/**
 * 渲染元素
 *
 * @param window_width 窗口宽度
 * @param window_height 窗口高度
 */
void Sprite::render(int window_width, int window_height) {
    m_shader->use();

    m_shader->setMat4("model", *m_model);

    if (m_view) {
        m_shader->setMat4("view", *m_view);
    }
    if (m_projection) {
        m_shader->setMat4("projection", *m_projection);
    }
}

void Sprite::setModel(const glm::mat4 &mat) {
    m_model = new glm::mat4(mat);
}
