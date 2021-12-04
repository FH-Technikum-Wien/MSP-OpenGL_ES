#pragma once

#include <map>
#include <string>

#include <android/asset_manager_jni.h>
#include <android/log.h>

class AssetManager {
public:
    AssetManager() = default;

    void Initialize(AAssetManager* assetManager);
    char* GetAsset(const char* assetPath);

private:
    AAssetManager* aAssetManager;
};