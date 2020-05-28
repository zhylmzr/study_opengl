#include "graphic.h"
#include "shader.h"
#include "rect.h"
#include "ui.h"
#include "circle.h"

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 300;

int main(int argc, char **args) {
    Graphic graphic("OpenGL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT);

    graphic.init();

    Shader shader("../resources/shader/vertex.glsl", "../resources/shader/fragment.glsl");
    shader.use();

    Rect rect(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    graphic.add_obj(&rect, &shader);

    Circle circle(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2);
    circle.setCenter(0, 0, 0);
    graphic.add_obj(&circle, &shader);

//    ui_init(graphic.getWindow());
    while (!graphic.termination()) {
        graphic.render_start();
//        ui_draw();
        graphic.render();
        graphic.render_end();
    }

//    ui_release();
    graphic.release();
    return 0;
}
