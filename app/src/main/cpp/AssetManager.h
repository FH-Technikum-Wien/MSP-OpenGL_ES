#pragma once

#include <map>
#include <string>

#include <android/asset_manager_jni.h>
#include <android/log.h>

class AssetManager {
public:
    AssetManager() = default;

    void Initialize(AAssetManager* assetManager);
    long GetAssetLength(const char* assetPath);
    char* GetAsset(const char* assetPath);
    char* GetBinaryAsset(const char* assetPath);

private:
    AAssetManager* aAssetManager;
};