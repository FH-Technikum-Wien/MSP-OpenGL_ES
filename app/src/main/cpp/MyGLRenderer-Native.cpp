#include <jni.h>
#include <android/log.h>
#include <GLES3/gl32.h>



#define LOG_TAG "MyGLRenderer-Native"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


extern "C"
JNIEXPORT void JNICALL
Java_at_davidpgl_opengles_MyGLRenderer_onSurfaceCreatedNative(JNIEnv *env, jobject thiz,
                                                              jobject gl10, jobject egl_config) {
    glClearColor(0.0f,0.0f,1.0f,1.0f);
}

extern "C"
JNIEXPORT void JNICALL
Java_at_davidpgl_opengles_MyGLRenderer_onSurfaceChangedNative(JNIEnv *env, jobject thiz,
                                                              jobject gl10, jint width,
                                                              jint height) {
    glViewport(0,0, width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_at_davidpgl_opengles_MyGLRenderer_onDrawFrameNative(JNIEnv *env, jobject thiz, jobject gl10) {
    glClear(GL_COLOR_BUFFER_BIT);
}