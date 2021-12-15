package at.davidpgl.opengles;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;

import java.io.InputStream;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyGLRenderer implements GLSurfaceView.Renderer {
    private Context activityContext;
    private AssetManager assetManager;


    public MyGLRenderer(Context context) {
        activityContext = context;
        this.assetManager = context.getResources().getAssets();
    }


    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        onSurfaceCreatedNative(gl, config, assetManager);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        onSurfaceChangedNative(gl, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        onDrawFrameNative(gl);
    }


    public native void onSurfaceCreatedNative(GL10 gl10, EGLConfig eglConfig, AssetManager assetManager);

    public native void onSurfaceChangedNative(GL10 gl10, int width, int height);

    public native void onDrawFrameNative(GL10 gl10);

}
