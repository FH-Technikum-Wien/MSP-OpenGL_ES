#include "AssetManager.h"
#include "Application.h"

AssetManager assetManager;
Application application;
bool ready = false;

extern "C"
JNIEXPORT void JNICALL
Java_at_davidpgl_opengles_MyGLRenderer_onSurfaceCreatedNative(JNIEnv *env, jobject thiz,
                                                              jobject gl10, jobject egl_config,
                                                              jobject asset_manager) {
    assetManager.Initialize(AAssetManager_fromJava(env, asset_manager));
    application.Initialize(assetManager);
    ready = true;
}

extern "C"
JNIEXPORT void JNICALL
Java_at_davidpgl_opengles_MyGLRenderer_onSurfaceChangedNative(JNIEnv *env, jobject thiz,
                                                              jobject gl10, jint width,
                                                              jint height) {
    application.SetScreenSize(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_at_davidpgl_opengles_MyGLRenderer_onDrawFrameNative(JNIEnv *env, jobject thiz, jobject gl10) {
    if(!ready)
        return;
    application.Tick();
}
