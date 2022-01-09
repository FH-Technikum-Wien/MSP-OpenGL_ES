#include "Application.h"


void Application::Initialize(AssetManager &assetManager) {
    renderer.Initialize(assetManager);
    lastFrameTime = clock.now();
}

void Application::Tick(){
    // Calculate deltaTime in seconds
    auto currentFrameTime = clock.now();
    double deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentFrameTime - lastFrameTime).count() / 1e9;
    lastFrameTime = currentFrameTime;

    // Produced time that can be consumed
    fixedUpdateAccumulator += deltaTime;

    // Repeat physics updates as long as there is time remaining or skip it
    while (fixedUpdateAccumulator >= FIXED_DELTA_TIME)
    {

        // Execute FixedUpdate
        FixedUpdate(FIXED_DELTA_TIME);

        // Reduce leftover time
        fixedUpdateAccumulator -= FIXED_DELTA_TIME;
    }

    // TODO: Input

    Update(deltaTime);

    renderer.Render();
}

void Application::Update(double deltaTime) {

}

void Application::FixedUpdate(double fixeDeltaTime) {

}

void Application::SetScreenSize(float screenWidth, float screenHeight) {
    renderer.SetScreenSize(screenWidth, screenHeight);
}
