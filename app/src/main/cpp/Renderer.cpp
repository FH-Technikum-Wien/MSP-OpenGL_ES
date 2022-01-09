#include "Renderer.h"

#include <jni.h>
#include <android/log.h>
#include <GLES3/gl3.h>

#include "OBJ_Loader.h"


#undef LOG_TAG
#define LOG_TAG "RENDERER"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

objl::Loader loader;


Renderer::~Renderer() {
    delete object;
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

    object->Render(shader);
    //cube->Rotate(glm::vec3(0.5f, 1, 0));
}

void Renderer::Initialize(AssetManager &assetManager) {
    LOGI("Current OpenGLES Version: %s", glGetString(GL_VERSION));
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    char* vertexShaderCode = assetManager.GetAsset("Shaders/Shader.vert");
    char* fragmentShaderCode = assetManager.GetAsset("Shaders/Shader.frag");

    shader.AddShader(vertexShaderCode, VERTEX_SHADER);
    shader.AddShader(fragmentShaderCode, FRAGMENT_SHADER);
    shader.linkProgram();

    delete vertexShaderCode;
    delete fragmentShaderCode;

    loader.LoadFile("Resources/cottage_obj.obj", assetManager);

    // Convert obj-object to internal object
    std::vector<float>* vertices = new std::vector<float>();
    std::vector<float>* normals = new std::vector<float>();
    std::vector<float>* uvs = new std::vector<float>();
    for (const objl::Vertex& vertex : loader.LoadedVertices)
    {
        vertices->push_back(vertex.Position.X);
        vertices->push_back(vertex.Position.Y);
        vertices->push_back(vertex.Position.Z);

        normals->push_back(vertex.Normal.X);
        normals->push_back(vertex.Normal.Y);
        normals->push_back(vertex.Normal.Z);

        uvs->push_back(vertex.TextureCoordinate.X);
        uvs->push_back(vertex.TextureCoordinate.Y);
    }

    std::vector<unsigned int>* indices = new std::vector<unsigned int>(loader.LoadedIndices);

    char* texture = assetManager.GetAsset("textures#tcf_etc2/wood.pkm");
    Material material = Material(texture);
    object = new Object(material, glm::vec3(0, -20, -80), glm::vec3(0, 60, 0), glm::vec3(1));
    object->vertices = vertices->data();
    object->normals = normals->data();
    object->indices = indices->data();
    object->uvs = uvs->data();

    object->vertexCount = vertices->size();
    object->indexCount = indices->size();


    object->Initialize();

    //delete texture;
}
