#include "Renderer.h"

#include <jni.h>
#include <android/log.h>
#include <GLES3/gl3.h>
#include "OBJ_Loader.h"


#undef LOG_TAG
#define LOG_TAG "RENDERER"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


Renderer::~Renderer() {
    delete cube;
}

void Renderer::SetScreenSize(const float width, const float height) {
    screenWidth = width;
    screenHeight = height;
    camera.SetScreenSize(width, height);
}

void Renderer::Render() {
    // Sets one color for window (background)
    glClearColor(0.2f, 0.4f, 0.4f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.Activate();
    shader.setMat4("projectionMat", camera.ProjectionMat);
    shader.setMat4("viewMat", camera.GetViewMat());

    glViewport(0, 0, screenWidth, screenHeight);

    cube->Render(shader);
    cube->Rotate(glm::vec3(0.5f, 1, 0));
}

void Renderer::Initialize(AssetManager &assetManager) {
    LOGI("Current OpenGLES Version: %s", glGetString(GL_VERSION));
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    cube = new Cube(glm::vec3(0, 0, 0), glm::vec3(0, 45, 0));

    char* vertexShaderCode = assetManager.GetAsset("Shaders/Shader.vert");
    char* fragmentShaderCode = assetManager.GetAsset("Shaders/Shader.frag");

    shader.AddShader(vertexShaderCode, VERTEX_SHADER);
    shader.AddShader(fragmentShaderCode, FRAGMENT_SHADER);
    shader.linkProgram();

    delete vertexShaderCode;
    delete fragmentShaderCode;

    objl::Loader loader;

    bool loadout = loader.LoadFile("Resources/cottage_obj.obj", assetManager);
    loader.LoadedVertices;
}
