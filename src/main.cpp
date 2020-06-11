#include "graphic.h"
#include "shader.h"
#include "ui.h"
#include "cube.h"
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 300;

using namespace std;

Camera *camera;

void processInput(GLFWwindow *window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->processKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->processKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->processKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->processKeyboard(RIGHT, deltaTime);
    }
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos) {
    static float lastX, lastY;
    static bool firstMouse = true;

    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    camera->processMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset) {
    camera->processMouseScroll(yOffset);
}

int main(int argc, char **args) {
    Graphic graphic("OpenGL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT);

    graphic.init();

    Shader shader("../resources/shader/vertex.glsl", "../resources/shader/fragment.glsl");
    shader.use();

    vector<Sprite *> cubes;

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    for (int i = 0; i < 10; i++) {
        Cube *cube = new Cube;
        glm::mat4 model;
        model = glm::translate(glm::mat4{1.0f}, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        model = glm::scale(model, glm::vec3(0.5f));
        cube->setModel(model);
        graphic.addSprite(cube, &shader);
    }

    camera = new Camera(glm::vec3(0, 0, 3), glm::vec3(0, 1, 0));
    graphic.addSprite(camera, &shader);

    glfwSetInputMode(graphic.getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPosCallback(graphic.getWindow(), mouse_callback);
    glfwSetScrollCallback(graphic.getWindow(), scroll_callback);

    float deltaTime = 0.0f;
    float lastTime = 0.0f;

    while (!graphic.termination()) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;
        graphic.renderStart();
        processInput(graphic.getWindow(), deltaTime);
        graphic.render();
        graphic.renderEnd();
    }

    graphic.release();
    return 0;
}
