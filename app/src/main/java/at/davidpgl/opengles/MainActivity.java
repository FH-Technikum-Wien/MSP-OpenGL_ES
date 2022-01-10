package at.davidpgl.opengles;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.view.GestureDetectorCompat;

import android.os.Bundle;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;

import at.davidpgl.opengles.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
    public static final String LOG_TAG = "MainActivity";

    // Used to load the 'opengles' library on application startup.
    static {
        System.loadLibrary("opengles");
    }

    private ActivityMainBinding binding;

    private GestureDetectorCompat detector;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        detector = new GestureDetectorCompat(this, new MyGestureListener());

    }

    @Override
    public boolean onTouchEvent(MotionEvent event){
        this.detector.onTouchEvent(event);

        return super.onTouchEvent(event);
    }

    class MyGestureListener extends GestureDetector.SimpleOnGestureListener {

        @Override
        public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
            onScrollNative(distanceX, distanceY);
            return super.onScroll(e1, e2, distanceX, distanceY);
        }
    }

    public native void onScrollNative(float distanceX, float distanceY);


}