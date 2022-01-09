#pragma once

#include "Renderer.h"

class Application {
public:
    void Initialize(AssetManager &assetManager);
    void Tick();
    void Update(double deltaTime);
    void FixedUpdate(double fixeDeltaTime);

    void SetScreenSize(float screenWidth, float screenHeight);

private:
    Renderer renderer;
    std::chrono::high_resolution_clock clock;

    std::chrono::steady_clock::time_point lastFrameTime;
    double fixedUpdateAccumulator = 0.0f;

private:
    // The fixed time step used for the physics calculation.
    const double FIXED_DELTA_TIME = 1.0f / 100.0f;
};
