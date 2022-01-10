#include "Renderer.h"

#include <jni.h>
#include <android/log.h>
#include <GLES3/gl3.h>

#include <glm/gtx/rotate_vector.hpp>
#include "OBJ_Loader.h"


#undef LOG_TAG
#define LOG_TAG "RENDERER"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

objl::Loader loader;


Renderer::~Renderer() {
    delete object;
    delete fasterObject;
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
    if(object != nullptr)
        object->Render(shader);
    else if(fasterObject != nullptr)
        fasterObject->Render(shader);
}

void Renderer::Initialize(AssetManager &assetManager) {
    this->assetManager = assetManager;
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


    //LoadNormal();
    LoadBinary();
}

void Renderer::LoadNormal() {
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
    object->indices = indices->data();
    object->uvs = uvs->data();

    object->vertexCount = vertices->size();
    object->indexCount = indices->size();


    object->Initialize();

    delete texture;
}

void Renderer::LoadBinary() {

    char* asset = assetManager.GetBinaryAsset("Resources/cottage_obj.bin");

    unsigned int vertexCount = ((unsigned int*)asset)[0];
    unsigned int indexCount = ((unsigned int*)asset)[1];

    float* data = (float*)(((unsigned int*)asset) + 2);
    unsigned int* indices = (unsigned int *)(data + vertexCount * 5);

    char* texture = assetManager.GetAsset("textures#tcf_etc2/wood.pkm");

    Material material = Material(texture);
    fasterObject = new FasterObject(material, glm::vec3(0, -20, -80), glm::vec3(0, 60, 0), glm::vec3(1));
    fasterObject->data = data;
    fasterObject->indices = indices;

    fasterObject->vertexCount = vertexCount;
    fasterObject->indexCount = indexCount;

    fasterObject->Initialize();

    delete texture;
    delete asset;
}

void Renderer::Scroll(float distanceX, float distanceY) {
    scrollX += distanceX * 0.00001f;
    scrollY += distanceY * 0.00001f;
    fasterObject->Rotate(glm::vec3(distanceY * 0.1f, distanceX * 0.1f, 0.0f));
}

void Renderer::Zoom(float zoomFactor) {
    camera.Position = glm::mix(camera.Position, glm::vec3(0,0,0), zoomFactor);
}
