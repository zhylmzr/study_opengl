#include "graphic.h"
#include "shader.h"
#include "rect.h"

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 300;

int main(int argc, char **args) {
    Graphic graphic("OpenGL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT);

    graphic.init();

    Shader shader("../resources/shader/vertex.glsl", "../resources/shader/fragment.glsl");
    shader.use();

    Rect rect(-SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    graphic.add_obj(&rect, &shader);

    while (!graphic.termination()) {
        graphic.render_start();
        graphic.render();
        graphic.render_end();
    }

    graphic.release();
    return 0;
}
