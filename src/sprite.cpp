#include "sprite.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


void Sprite::use_shader(Shader *shader) {
    m_shader = shader;
}

Sprite::~Sprite() {
    SAFE_DELETE_BUFFER(m_vao)
    SAFE_DELETE_BUFFER(m_vbo)
    SAFE_DELETE_BUFFER(m_vbo)
}

void Sprite::render(int window_width, int window_height) const {
    m_shader->use();
    glm::mat4 transform{1};

    float scale_x = (float) m_width / (float) window_width;
    float scale_y = (float) m_height / (float) window_height;

    float current_x = -scale_x;
    float current_y = scale_y;

    float target_x = (float) m_x / ((float) window_width / 2);
    float target_y = (float) m_y / ((float) window_height / 2);

    transform = glm::translate(transform, glm::vec3(target_x - current_x, target_y - current_y, 0.0f));
    transform = glm::scale(transform, glm::vec3(scale_x, scale_y, 0));
    m_shader->setMat4("model", transform);
}
