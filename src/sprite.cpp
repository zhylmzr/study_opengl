#include "sprite.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Sprite::Sprite() {
    m_shader = nullptr;
    m_view = glm::translate(glm::mat4{1}, glm::vec3(0, 0, -1));
}

void Sprite::useShader(Shader *shader) {
    m_shader = shader;
}

Sprite::~Sprite() {
    SAFE_DELETE_BUFFER(m_vao)
    SAFE_DELETE_BUFFER(m_vbo)
    SAFE_DELETE_BUFFER(m_vbo)
}

/**
 * 渲染元素
 *
 * @param window_width 窗口宽度
 * @param window_height 窗口高度
 */
void Sprite::render(int window_width, int window_height) {
    m_shader->use();

    m_projection = glm::perspective(glm::radians(90.0f), (float) window_width / window_height, 0.1f, 100.0f);

    m_shader->setMat4("model", m_model);
    m_shader->setMat4("view", m_view);
    m_shader->setMat4("projection", m_projection);
}

void Sprite::setModel(const glm::mat4 &mat) {
    m_model = mat;
}
