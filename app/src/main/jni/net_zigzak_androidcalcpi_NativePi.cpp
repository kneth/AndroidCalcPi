#include <stdexcept>
#include <sstream>

#include <jni.h>

#include "net_zigzak_androidcalcpi_NativePi.h"
#include "pi.hpp"

JNIEXPORT jlong JNICALL Java_net_zigzak_androidcalcpi_NativePi_nativeCreate
  (JNIEnv *env, jobject, jlong iterations)
{
    Pi *pi = new Pi(static_cast<long>(iterations));
    return reinterpret_cast<jlong>(pi);
}

JNIEXPORT jdouble JNICALL Java_net_zigzak_androidcalcpi_NativePi_nativeEstimate
  (JNIEnv *, jobject, jlong nativePtr)
{
    Pi *pi = reinterpret_cast<Pi *>(nativePtr);
    double estimate = pi->estimate();
    return estimate;
}

JNIEXPORT void JNICALL Java_net_zigzak_androidcalcpi_NativePi_nativeClose
(JNIEnv *, jobject, jlong nativePtr) {
    delete reinterpret_cast<Pi *>(nativePtr);
}