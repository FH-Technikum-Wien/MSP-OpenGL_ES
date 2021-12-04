package at.davidpgl.opengles;


import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class MyGLSurfaceView extends GLSurfaceView {
    private MyGLRenderer renderer;


    public MyGLSurfaceView(Context context) {
        super(context);
        init();
    }

    public MyGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init(){
        setEGLContextClientVersion(2);
        renderer = new MyGLRenderer(getContext());
        setRenderer(renderer);
    }
}
