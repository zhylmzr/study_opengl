#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(
        const glm::vec3 &position,
        const glm::vec3 &up,
        float yaw,
        float pitch) {
    m_position = position;
    m_worldUp = up;
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();

    init();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) {
    m_position = glm::vec3(posX, posY, posZ);
    m_worldUp = glm::vec3(upX, upY, upZ);
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();

    init();
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = m_movementSpeed * deltaTime;
    if (direction == FORWARD)
        m_position += m_front * velocity;
    if (direction == BACKWARD)
        m_position -= m_front * velocity;
    if (direction == LEFT)
        m_position -= m_right * velocity;
    if (direction == RIGHT)
        m_position += m_right * velocity;

    setViewMatrix();
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    xOffset *= m_mouseSensitivity;
    yOffset *= m_mouseSensitivity;

    m_yaw += xOffset;
    m_pitch += yOffset;

    if (constrainPitch) {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    updateCameraVectors();
    setViewMatrix();
}

void Camera::processMouseScroll(float yOffset) {
    m_zoom -= yOffset;
    if (m_zoom < 1.0f)
        m_zoom = 1.0f;
    if (m_zoom > 90.0f)
        m_zoom = 90.0f;

    setProjectMatrix();
}

void Camera::setViewMatrix() {
    delete m_view;
    m_view = new glm::mat4(glm::lookAt(m_position, m_position + m_front, m_up));
}

void Camera::setProjectMatrix() {
    delete m_projection;
    m_projection = new glm::mat4(glm::perspective(glm::radians(m_zoom), m_aspect, 0.1f, 100.0f));
}

void Camera::init() {
    setViewMatrix();
    setProjectMatrix();
}

void Camera::render(int window_width, int window_height) {
    Sprite::render(window_width, window_height);
    m_aspect = (float)window_width / window_height;
}
