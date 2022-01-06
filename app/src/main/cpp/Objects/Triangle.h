#pragma once

#include "Object.h"

class Triangle : public Object {
public:
    Triangle(glm::vec3 position, glm::vec3 eulerAngles) : Triangle(position, eulerAngles,
                                                                   glm::vec3(1)) {

    }

    Triangle(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale) : Object(position,
                                                                                  eulerAngles,
                                                                                  scale) {
        vertices = new float[9]{
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                1.0f, 1.0f, 0.0f,
        };

        normals = new float[9]{
                0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, -1.0f,
                0.0f, 0.0f, -1.0f,
        };

        uvs = new float[6]{
                scale.x, 0.0f,
                scale.x, scale.y,
                0.0f, 0.0f,
        };

        indices = new unsigned int[3]{
                0, 1, 2
        };

        vertexCount = 3;
        indexCount = 3;

        Initialize();
    }
};
