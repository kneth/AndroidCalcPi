package net.zigzak.androidcalcpi;

import java.io.Closeable;
import java.io.IOException;

public class NativePi implements Closeable {
    private long nativePtr;

    NativePi(long iterations) {
        nativePtr = nativeCreate(iterations);
    }

    native long nativeCreate(long iterations);

    double estimate() {
        return nativeEstimate(nativePtr);
    }

    native double nativeEstimate(long nativePtr);

    @Override
    public void close() throws IOException {
        nativeClose(nativePtr);
    }

    native void nativeClose(long nativePtr);
}
