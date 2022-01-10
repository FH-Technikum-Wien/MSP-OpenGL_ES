package at.davidpgl.opengles;


import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;

public class MyGLSurfaceView extends GLSurfaceView {
    private MyGLRenderer renderer;

    private ScaleGestureDetector scaleDetector;


    public MyGLSurfaceView(Context context) {
        super(context);
        init();
    }

    public MyGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();

        scaleDetector = new ScaleGestureDetector(context, new ScaleListener());
    }

    private void init(){
        setEGLContextClientVersion(2);
        renderer = new MyGLRenderer(getContext());
        setRenderer(renderer);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        scaleDetector.onTouchEvent(event);
        return super.onTouchEvent(event);
    }

    private class ScaleListener
            extends ScaleGestureDetector.SimpleOnScaleGestureListener {
        @Override
        public boolean onScale(ScaleGestureDetector detector) {
            Log.i("TEST", "onTouchEvent: ");
            onScaleNative(detector.getScaleFactor());
            return true;
        }

        
    }

    public native void onScaleNative(float scaleFactor);
}
