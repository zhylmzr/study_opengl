#include "graphic.h"
#include "shader.h"

int main(int argc, char ** args) {
    Graphic graphic("OpenGL Tutorial", 640, 480);

    graphic.init();

    Shader shader("../resources/shader/vertex.glsl", "../resources/shader/fragment.glsl");
    shader.use();

    while(!graphic.termination()) {
        graphic.render_start();
        graphic.render(shader);
        graphic.render_end();
    }

    graphic.release();
    return 0;
}
