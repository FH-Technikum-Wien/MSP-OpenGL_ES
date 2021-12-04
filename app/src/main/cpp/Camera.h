#pragma once

#include <glm\vec3.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\transform.hpp>

class Camera {
public:
    Camera() = default;

    Camera(glm::vec3 position) : Position(position) {

    }

    Camera(glm::vec3 position, glm::vec3 eulerAngles) : Position(position), Orientation(
            glm::quat(glm::radians(eulerAngles))) {

    }

    void SetScreenSize(const float screenWidth, const float screenHeight) {
        ProjectionMat = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f,
                                         100.0f);
    }

    glm::mat4 GetViewMat() const {
        return glm::inverse(glm::translate(transform, Position) * glm::mat4_cast(Orientation));
    }

public:
    glm::mat4 ProjectionMat = glm::mat4(1);
    glm::vec3 Position = glm::vec3(0.0f);
    glm::quat Orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));

private:
    glm::mat4 transform = glm::mat4(1.0f);
};