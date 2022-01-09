#include "AssetManager.h"

#undef LOG_TAG
#define LOG_TAG "ASSET_MANAGER"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void AssetManager::Initialize(AAssetManager *assetManager) {
    aAssetManager = assetManager;
}

long AssetManager::GetAssetLength(const char *assetPath){
    AAsset *asset = AAssetManager_open(aAssetManager, assetPath, AASSET_MODE_BUFFER);

    // With zero termination
    return AAsset_getLength(asset) + 1;
}

char *AssetManager::GetAsset(const char *assetPath) {
    AAsset *asset = AAssetManager_open(aAssetManager, assetPath, AASSET_MODE_BUFFER);

    off_t fileLength = AAsset_getLength(asset);
    char *fileContent = new char[fileLength + 1];

    AAsset_read(asset, fileContent, fileLength);
    // Zero-terminate file for safety
    fileContent[fileLength] = '\0';

    AAsset_close(asset);

    return fileContent;
}

const char *AssetManager::GetBinaryAsset(const char *assetPath) {
    AAsset *asset = AAssetManager_open(aAssetManager, assetPath, AASSET_MODE_BUFFER);

    off_t fileLength = AAsset_getLength(asset);

    const char* fileContent = static_cast<const char*>(AAsset_getBuffer(asset));

    AAsset_close(asset);

    return fileContent;
}




