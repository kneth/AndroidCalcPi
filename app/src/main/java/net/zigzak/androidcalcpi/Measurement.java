package net.zigzak.androidcalcpi;


import android.os.Debug;
import android.util.Log;

public abstract class Measurement {
    private long resolution;

    public Measurement() {
        // does CPU timer work?
        if (Debug.threadCpuTimeNanos() == -1) {
            throw new RuntimeException("Debug.threadCpuTimeNanos() doesn't work.");
        }

        // resolution/granularity of timer
        // see http://gamasutra.com/view/feature/171774/getting_high_precision_timing_on_.php?print=1
        long diff = 50000; // very large value
        for (int i = 0; i < 100; i++) {
            long end;
            long start = Debug.threadCpuTimeNanos();
            while (true) {
                end = Debug.threadCpuTimeNanos();
                if (end != start) {
                    if (diff > (end - start)) {
                        diff = end - start;
                    }
                    break;
                }
            }
        }
        resolution = diff;
    }

    public abstract void run();

    public void execute(String message) {
        long start = Debug.threadCpuTimeNanos();
        run();
        long stop = Debug.threadCpuTimeNanos();
        long duration = stop - start;
        if (duration < resolution) {
            throw new RuntimeException("Too short");
        }
        Log.d("calcPi", String.format("%s: %d", message, duration));
    }
}