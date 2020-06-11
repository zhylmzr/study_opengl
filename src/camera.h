#pragma once

#include "sprite.h"
#include <glm/glm.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const float ASPECT = 1.0f;

class Camera : public Sprite {
public:
    Camera(const glm::vec3 &position, const glm::vec3 &up, float yaw = YAW, float pitch = PITCH);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    void processKeyboard(Camera_Movement direction, float deltaTime);

    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

    void init() override;

    void processMouseScroll(float yOffset);

    void render(int window_width, int window_height) override;

private:
    glm::vec3 m_position;
    glm::vec3 m_front = glm::vec3(0, 0, -1);
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    float m_yaw;
    float m_pitch;

    float m_movementSpeed = SPEED;
    float m_mouseSensitivity = SENSITIVITY;
    float m_zoom = ZOOM;
    float m_aspect = ASPECT;

    void updateCameraVectors();

    void setViewMatrix();

    void setProjectMatrix();
};