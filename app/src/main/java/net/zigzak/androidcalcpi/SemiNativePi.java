package net.zigzak.androidcalcpi;

import java.io.Closeable;
import java.io.IOException;

public class SemiNativePi implements Closeable {
    private NativeRNG nativeRNG;
    private long iterations;

    SemiNativePi(long iterations) {
        if (iterations > 0) {
            nativeRNG = new NativeRNG(1);
            this.iterations = iterations;
        } else {
            throw new IllegalArgumentException("Number of iterations must be at least 1.");
        }
    }

    double estimate() {
        long nHits = 0;
        for (int i = 0; i < iterations; i++) {
            double x = nativeRNG.uniform();
            double y = nativeRNG.uniform();
            if (x*x+y*y < 1.0) { // square root not really needed!
                nHits++;
            }
        }
        return 4.0*(double)nHits/(double)iterations;
    }

    @Override
    public void close() throws IOException {
        nativeRNG.close();
    }
}
