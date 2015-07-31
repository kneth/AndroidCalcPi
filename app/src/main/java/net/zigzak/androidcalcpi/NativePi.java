package net.zigzak.androidcalcpi;

import java.io.Closeable;
import java.io.IOException;

public class NativePi implements Closeable {
    private long nativePtr;

    NativePi(long iterations, long generators) {
        nativePtr = nativeCreate(iterations, generators);
    }

    native long nativeCreate(long iterations, long generators);

    double estimate() {
        return nativeEstimate(nativePtr);
    }

    native double nativeEstimate(long nativePtr);

    double estimate(long numThreads) {
        return nativeEstimateThread(nativePtr, numThreads);
    }

    native double nativeEstimateThread(long nativePtr, long numThreads);

    @Override
    public void close() throws IOException {
        nativeClose(nativePtr);
    }

    native void nativeClose(long nativePtr);
}
