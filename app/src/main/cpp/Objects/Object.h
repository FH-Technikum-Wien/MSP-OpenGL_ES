#pragma once

#include "Material.h"
#include "Shader.h"


class Object {
public:
    glm::mat4 transform = glm::mat4(1.0f);
    float* vertices{};
    float* uvs{};
    unsigned int* indices{};

    unsigned int vertexCount = 0;
    unsigned int indexCount = 0;

    Material material;

public:
    Object(Material material, const glm::vec3 position, const glm::vec3 eulerAngles, const glm::vec3 scaleFactor);

    ~Object();

    void Initialize();

    void Render(const Shader& shader) const;

    void Translate(glm::vec3 translation);
    void Scale(glm::vec3 scaleFactor);
    void Rotate(glm::vec3 eulerAngles);

private:
    unsigned int VAO = 0;
    unsigned int EBO = 0;
    unsigned int VBO_VERTICES = 0;
    unsigned int VBO_UVS = 0;

};
