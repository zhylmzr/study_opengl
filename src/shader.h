//
// Created by zhylmzr on 2020/5/20.
//
#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Shader {
public:
    unsigned ID;

    Shader(const char *vertexPath, const char *fragmentPath);

    void use() const;

    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
private:
    static void checkCompileErrors(GLuint shader, const std::string& type);
};
