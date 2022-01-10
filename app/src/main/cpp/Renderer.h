#pragma once

#include <Objects/FasterObject.h>
#include "Objects/Plane.h"
#include "Shader.h"
#include "Objects/Cube.h"
#include "Camera.h"
#include "AssetManager.h"

class Renderer {
public:
    Renderer() = default;

    ~Renderer();

    void Initialize(AssetManager &assetManager);

    void LoadNormal();

    void LoadBinary();

    void SetScreenSize(float screenWidth, float screenHeight);

    void Render();

    void Scroll(float distanceX, float distanceY);

    void Zoom(float zoomFactor);

private:
    AssetManager assetManager;

    Shader shader;
    Camera camera = Camera(glm::vec3(0, 4, 10), glm::vec3(-15,0,0));

    Object* object = nullptr;
    FasterObject* fasterObject = nullptr;

    float screenWidth = 0.0f;
    float screenHeight = 0.0f;

    float scrollX = 0.0f;
    float scrollY = 0.0f;
};