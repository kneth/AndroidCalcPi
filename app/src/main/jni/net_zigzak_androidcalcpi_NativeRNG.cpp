#include "net_zigzak_androidcalcpi_NativeRNG.h"
#include "RNG.hpp"

JNIEXPORT jlong JNICALL Java_net_zigzak_androidcalcpi_NativeRNG_nativeCreate
(JNIEnv *, jobject, jlong seed) {
    RNG *rng = new RNG(static_cast<long>(seed));
    return reinterpret_cast<jlong>(rng);
}

JNIEXPORT jdouble JNICALL Java_net_zigzak_androidcalcpi_NativeRNG_nativeUniform
  (JNIEnv *, jobject, jlong nativePtr)
{
    RNG *rng = reinterpret_cast<RNG *>(nativePtr);
    return rng->uniform();
}

JNIEXPORT jdoubleArray JNICALL Java_net_zigzak_androidcalcpi_NativeRNG_nativeGauss2d
  (JNIEnv *, jobject, jlong nativePtr)
{
    RNG *rng = reinterpret_cast<RNG *>(nativePtr);
    // TODO
}

JNIEXPORT void JNICALL Java_net_zigzak_androidcalcpi_NativeRNG_nativeClose
  (JNIEnv *, jobject, jlong nativePtr)
{
    RNG *rng = reinterpret_cast<RNG *>(nativePtr);
    delete rng;
}