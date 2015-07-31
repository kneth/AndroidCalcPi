#include <stdexcept>
#include <sstream>

#include <jni.h>

#include "net_zigzak_androidcalcpi_NativePi.h"
#include "pi.hpp"
#include "util.hpp"

JNIEXPORT jlong JNICALL Java_net_zigzak_androidcalcpi_NativePi_nativeCreate
  (JNIEnv *env, jobject, jlong iterations)
{
    ENTER()
    try {
        LOG("iterations: %ld", S64(iterations))
        Pi *pi = new Pi(static_cast<long>(iterations));
        return reinterpret_cast<jlong>(pi);
    }
    catch (std::exception& e) {
        LOG("Exception in %s", __FUNCTION__)
        jclass jExceptionClass = env->FindClass("java/lang/RuntimeException");
        std::ostringstream message;
        message << "Allocating native class Pi failed: " << e.what();
        env->ThrowNew(jExceptionClass, message.str().c_str());
        env->DeleteLocalRef(jExceptionClass);
    }
    return 0;
}

JNIEXPORT jdouble JNICALL Java_net_zigzak_androidcalcpi_NativePi_nativeEstimate
  (JNIEnv *, jobject, jlong nativePtr)
{
    ENTER_PTR(nativePtr)
    Pi *pi = reinterpret_cast<Pi *>(nativePtr);
    double estimate = pi->estimate();
    LOG("estimate = %e", estimate)
    return estimate;
}

JNIEXPORT void JNICALL Java_net_zigzak_androidcalcpi_NativePi_nativeClose
(JNIEnv *, jobject, jlong nativePtr) {
    ENTER_PTR(nativePtr)
    delete reinterpret_cast<Pi *>(nativePtr);
}