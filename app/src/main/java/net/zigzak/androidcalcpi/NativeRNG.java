package net.zigzak.androidcalcpi;

import java.io.Closeable;
import java.io.IOException;

public class NativeRNG implements Closeable {
    private long nativePtr;

    NativeRNG(long seed) {
        nativePtr = nativeCreate(seed);
    }

    native long nativeCreate(long seed);

    public double uniform() {
        return nativeUniform(nativePtr);
    }

    native double nativeUniform(long nativePtr);

    public double[] gauss2d() {
        return nativeGauss2d(nativePtr);
    }

    native double[] nativeGauss2d(long nativePtr);

    @Override
    public void close() throws IOException {
        nativeClose(nativePtr);
    }

    native void nativeClose(long nativePtr);
}
