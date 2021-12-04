#pragma once
#include "Shader.h"


class Object {
public:
    glm::mat4 transform = glm::mat4(1.0f);
    float* vertices{};
    float* normals{};
    float* uvs{};
    unsigned int* indices{};

public:
    Object(const glm::vec3 position, const glm::vec3 eulerAngles, const glm::vec3 scaleFactor);

    ~Object();

    void Render(const Shader& shader) const;


    void Translate(glm::vec3 translation);
    void Scale(glm::vec3 scaleFactor);
    void Rotate(glm::vec3 eulerAngles);


protected:
    unsigned int vertexCount = 0;
    unsigned int indexCount = 0;

protected:
    void initialize();

private:
    unsigned int VAO = 0;
    unsigned int EBO = 0;
    unsigned int VBO_VERTICES = 0;
    unsigned int VBO_NORMALS = 0;
    unsigned int VBO_UVS = 0;

};
