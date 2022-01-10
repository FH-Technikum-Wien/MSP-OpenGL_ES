#pragma once

#include "Renderer.h"

class Application {
public:
    void Initialize(AssetManager &assetManager);
    void Tick();
    void Update(double deltaTime);
    void FixedUpdate(double fixeDeltaTime);

    void HandleScroll(float distanceX, float distanceY);
    void HandleScale(float scaleFactor);

    void SetScreenSize(float screenWidth, float screenHeight);

private:
    Renderer renderer;
    std::chrono::high_resolution_clock clock;

    std::chrono::steady_clock::time_point lastFrameTime;
    double fixedUpdateAccumulator = 0.0f;

    double deltaAccumulator = 0.0f;
    double averageFrameTime = 0.0f;
    int frames = 0;

private:
    // The fixed time step used for the physics calculation.
    const double FIXED_DELTA_TIME = 1.0f / 100.0f;
};
