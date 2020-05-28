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

/**
 * 渲染元素
 *
 * 重建坐标系: 以窗口左上角为原点, 屏幕右下方向为坐标轴正方向, 窗口宽高为坐标轴可视范围最大值
 * @param window_width 窗口宽度
 * @param window_height 窗口高度
 */
void Sprite::render(int window_width, int window_height) const {
    m_shader->use();
    glm::mat4 transform{1};

    // y轴翻转, x轴不变
    float scale_x = m_size[0] / (float) window_width;
    float scale_y = -m_size[1] / (float) window_height;

    float offset_x = (m_center[0] * m_size[0] / window_width) * 2;
    float offset_y = (m_center[1] * m_size[1] / window_height) * 2;

    float current_x = offset_x;
    float current_y = -offset_y;

    float target_x = m_position[0] / ((float) window_width / 2);
    float target_y = -m_position[1] / ((float) window_height / 2);

    transform = glm::translate(transform, glm::vec3(target_x - current_x, target_y - current_y, 0.0f));
    // 坐标轴平移到左上角
    transform = glm::translate(transform, glm::vec3(-1+fabs(scale_x), 1-fabs(scale_y), 0.0f));
    transform = glm::scale(transform, glm::vec3(scale_x, scale_y, 0));
    m_shader->setMat4("model", transform);
}

void Sprite::setCenter(float x, float y, float z) {
    m_center[0] = x;
    m_center[1] = y;
}
