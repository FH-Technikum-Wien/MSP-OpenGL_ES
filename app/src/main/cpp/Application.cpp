#include "Application.h"

#undef LOG_TAG
#define LOG_TAG "APPLICATION"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


void Application::Initialize(AssetManager &assetManager) {
    auto before = clock.now();
    renderer.Initialize(assetManager);
    // In seconds
    double time = std::chrono::duration_cast<std::chrono::microseconds>(clock.now() - before).count() / 1e6;
    LOGI("Loading time: %f milliseconds", time * 1e3);
}

void Application::Tick(){
    // Calculate deltaTime in seconds
    auto currentFrameTime = clock.now();
    // In seconds
    double deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentFrameTime - lastFrameTime).count() / 1e6;
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
    deltaAccumulator += deltaTime;
    ++frames;
    if(deltaAccumulator >= 1) {
        double time = deltaAccumulator / frames;
        deltaAccumulator = 0;
        frames = 0;
        LOGI("Render time: %f milliseconds", time * 1e3);
    }
}

void Application::Update(double deltaTime) {

}

void Application::FixedUpdate(double fixeDeltaTime) {

}

void Application::SetScreenSize(float screenWidth, float screenHeight) {
    renderer.SetScreenSize(screenWidth, screenHeight);
}
