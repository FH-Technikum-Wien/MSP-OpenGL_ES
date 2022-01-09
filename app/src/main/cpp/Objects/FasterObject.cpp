#include "FasterObject.h"
#include <jni.h>

FasterObject::FasterObject(Material material, const glm::vec3 position, const glm::vec3 eulerAngles,
               const glm::vec3 scaleFactor) {
    Translate(position);
    Rotate(eulerAngles);
    Scale(scaleFactor);
    this->material = material;
}

FasterObject::~FasterObject() {
    delete[] data;
}

void FasterObject::Render(const Shader &shader) const {
    // Add texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, material.texture);

    glBindVertexArray(VAO);
    shader.setMat4("modelMat", transform);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_DATA);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void FasterObject::Initialize() {
    // Generate Vertex-Array-Object to store vertex attribute configuration and which VBO(s) to use
    glGenVertexArrays(1, &VAO);
    // Bind Vertex-Array-Object to configure VBO(s)
    glBindVertexArray(VAO);
    // Generate Vertex-Buffer-Object to manage memory on GPU and store vertices
    glGenBuffers(1, &VBO_DATA);
    // Bind Vertex-Buffer-Object to configure it
    glBindBuffer(GL_ARRAY_BUFFER, VBO_DATA);
    // Copy vertex data into buffer's memory (into VBO which is bound to GL_ARRAY_BUFFER)
    glBufferData(GL_ARRAY_BUFFER, (vertexCount * 5) * sizeof(float), data, GL_STATIC_DRAW);

    // POSITION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    // UVs
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices,
                 GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void FasterObject::Translate(glm::vec3 translation)
{
    transform = glm::translate(transform, translation);
}

void FasterObject::Scale(glm::vec3 scaleFactor)
{
    transform = glm::scale(transform, scaleFactor);
}

void FasterObject::Rotate(glm::vec3 eulerAngles)
{
    transform = glm::rotate(transform, glm::radians(eulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
}
