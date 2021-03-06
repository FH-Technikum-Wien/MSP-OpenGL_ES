#include "Object.h"
#include <jni.h>

Object::Object(Material material, const glm::vec3 position, const glm::vec3 eulerAngles,
               const glm::vec3 scaleFactor) {
    Translate(position);
    Rotate(eulerAngles);
    Scale(scaleFactor);
    this->material = material;
}

Object::~Object() {
    delete[] vertices;
    delete[] uvs;
    delete[] indices;
}

void Object::Render(const Shader &shader) const {
    // Add texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, material.texture);

    glBindVertexArray(VAO);
    shader.setMat4("modelMat", transform);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTICES);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void Object::Initialize() {
    // Generate Vertex-Array-Object to store vertex attribute configuration and which VBO(s) to use
    glGenVertexArrays(1, &VAO);
    // Bind Vertex-Array-Object to configure VBO(s)
    glBindVertexArray(VAO);
    // Generate Vertex-Buffer-Object to manage memory on GPU and store vertices
    glGenBuffers(1, &VBO_VERTICES);
    // Bind Vertex-Buffer-Object to configure it
    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTICES);
    // Copy vertex data into buffer's memory (into VBO which is bound to GL_ARRAY_BUFFER)
    glBufferData(GL_ARRAY_BUFFER, (vertexCount * 3) * sizeof(float), vertices, GL_STATIC_DRAW);

    // POSITION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices,
                 GL_STATIC_DRAW);

    // UVs
    glGenBuffers(1, &VBO_UVS);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_UVS);
    glBufferData(GL_ARRAY_BUFFER, (vertexCount * 2) * sizeof(float), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Object::Translate(glm::vec3 translation)
{
    transform = glm::translate(transform, translation);
}

void Object::Scale(glm::vec3 scaleFactor)
{
    transform = glm::scale(transform, scaleFactor);
}

void Object::Rotate(glm::vec3 eulerAngles)
{
    transform = glm::rotate(transform, glm::radians(eulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
}
