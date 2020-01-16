#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include "tex.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

char *vertexShaderSource = NULL;
char *fragmentShaderSource = NULL;

GLFWwindow *window;

unsigned int LoadShader(char **vs, char **fs) {
    // 顶点着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, vs, NULL);
    glCompileShader(vertexShader);

    // 片段着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, fs, NULL);
    glCompileShader(fragmentShader);

    // 着色器程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

// 顶点数组对象
unsigned int VAO;
// 顶点缓冲对象
unsigned int VBO;
// 着色器程序
unsigned int shaderProgram;
// 顶点索引缓冲
unsigned int EBO;
// 纹理
unsigned int texture;
unsigned int texture2;

char *openShader(const char* file) {
    FILE *fp = fopen(file, "r");
    fseek(fp, 0, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buf = (char *)calloc(sz+1, 1);
    fread(buf, sz, 1, fp);
    fclose(fp);
    return buf;
}

unsigned int uPoint;
unsigned int uCompare;

void init() {
    float vertices[] = {
        // 位置, 颜色, 纹理
        -0.5f, .5f, 0.0f,       1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, 0.5f,     0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f, 0.5f,     1.0f, 1.0f,
        0.5, -0.5f, 0.0f,       1.0f, 0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 3, 2
    };

    // 注意: OpenGL 核心模式要求必须使用VertexArrays, 否则不会进行任何绘制
    // 顶点数组对象
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // 顶点缓冲对象
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 顶点索引缓冲
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 加载着色器
    vertexShaderSource = openShader("./resources/shader/vertex.glsl");
    fragmentShaderSource = openShader("./resources/shader/fragment.glsl");

    // 着色器程序
    shaderProgram = LoadShader(&vertexShaderSource, &fragmentShaderSource);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7*sizeof(float)));
    glEnableVertexAttribArray(2);

    glUseProgram(shaderProgram);
    uPoint = glGetUniformLocation(shaderProgram, "uPoint");
    uCompare = glGetUniformLocation(shaderProgram, "uCompare");

    glEnable(GL_BLEND);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(1);
    int width, height, nrChannels;
    void *data = stbi_load("./resources/image/container.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("./resources/image/face.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
}

float gPonitX = 0.0f;
void draw() {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    glUniform3f(uPoint, gPonitX, 0.0f, 0.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glUniform3f(uPoint, 0.5f, 0.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void frame_change_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

float gCompare = 0.0f;
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
    ((glfwGetKey(window, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS) && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)) {
        glfwSetWindowShouldClose(window, 1);
        return;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        gCompare += 0.01f;
        if (gCompare >= 1.0f) {
            gCompare = 1.0f;
        }
        glUniform1f(uCompare, gCompare);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        gCompare -= 0.01f;
        if (gCompare <= 0.0f) {
            gCompare = 0.0f;
        }
        glUniform1f(uCompare, gCompare);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        gPonitX -= 0.01f;
        if (gPonitX <= -1.5f) {
            gPonitX = -1.5f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        gPonitX += 0.01f;
        if (gPonitX >= 1.5f) {
            gPonitX = 1.5f;
        }
    }
}


int main(int argc, char ** args) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_SAMPLES, 4);
    
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Tutorial", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_change_callback);
    
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // glEnable(GL_MULTISAMPLE);

    init();
    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}