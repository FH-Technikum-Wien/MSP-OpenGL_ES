#pragma once

#include "Object.h"

class Plane : public Object {
public:
    Plane(glm::vec3 position, glm::vec3 eulerAngles) : Plane(position, eulerAngles, glm::vec3(1)) {
    }

    Plane(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale) : Object(position,
                                                                               eulerAngles,
                                                                               scale) {
        glm::vec3 texScale = glm::vec3(scale);

        vertices = new float[18]{
                -1.0f, 1.0f, 0.0f,
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                -1.0f, 1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                1.0f, 1.0f, 0.0f,
        };

        normals = new float[18]{
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
        };

        uvs = new float[12]{
                0.0f, texScale.y,
                0.0f, 0.0f,
                texScale.x, 0.0f,
                0.0f, texScale.y,
                texScale.x, 0.0f,
                texScale.x, texScale.y,
        };

        indices = new unsigned int[6]{
                0, 1, 2,
                3, 4, 5
        };

        vertexCount = 6;
        indexCount = 6;

        Initialize();
    }
};
