#include "AssetManager.h"
#include "Renderer.h"

AssetManager assetManager;
Renderer renderer;
bool ready = false;

extern "C"
JNIEXPORT void JNICALL
Java_at_davidpgl_opengles_MyGLRenderer_onSurfaceCreatedNative(JNIEnv *env, jobject thiz,
                                                              jobject gl10, jobject egl_config,
                                                              jobject asset_manager) {
    assetManager.Initialize(AAssetManager_fromJava(env, asset_manager));
    renderer.Initialize(assetManager);
    ready = true;
}

extern "C"
JNIEXPORT void JNICALL
Java_at_davidpgl_opengles_MyAssetManager_createAssetManager(JNIEnv *env, jobject thiz,
                                                            jobject asset_manager) {

}



extern "C"
JNIEXPORT void JNICALL
Java_at_davidpgl_opengles_MyGLRenderer_onSurfaceChangedNative(JNIEnv *env, jobject thiz,
                                                              jobject gl10, jint width,
                                                              jint height) {
    renderer.SetScreenSize(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_at_davidpgl_opengles_MyGLRenderer_onDrawFrameNative(JNIEnv *env, jobject thiz, jobject gl10) {
    if(!ready)
        return;
    renderer.Render();
}
