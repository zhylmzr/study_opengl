#include "graphic.h"
#include "shader.h"
#include "ui.h"
#include "cube.h"
#include <glm/gtc/matrix_transform.hpp>

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 300;

int main(int argc, char **args) {
    Graphic graphic("OpenGL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT);

    graphic.init();

    Shader shader("../resources/shader/vertex.glsl", "../resources/shader/fragment.glsl");
    shader.use();

    Cube cube;
    glm::mat4 model{1};
    model = glm::translate(model, glm::vec3(0, 0, -1));
    model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
    model = glm::rotate(model, glm::radians(55.0f), glm::vec3(-1, 0, 0));
    cube.setModel(model);

    graphic.addSprite(&cube, &shader);

    while (!graphic.termination()) {
        graphic.renderStart();
        graphic.render();
        graphic.renderEnd();
    }

    graphic.release();
    return 0;
}
