/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class net_zigzak_androidcalcpi_NativeRNG */

#ifndef _Included_net_zigzak_androidcalcpi_NativeRNG
#define _Included_net_zigzak_androidcalcpi_NativeRNG
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     net_zigzak_androidcalcpi_NativeRNG
 * Method:    nativeCreate
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_net_zigzak_androidcalcpi_NativeRNG_nativeCreate
  (JNIEnv *, jobject, jlong);

/*
 * Class:     net_zigzak_androidcalcpi_NativeRNG
 * Method:    nativeUniform
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_net_zigzak_androidcalcpi_NativeRNG_nativeUniform
  (JNIEnv *, jobject, jlong);

/*
 * Class:     net_zigzak_androidcalcpi_NativeRNG
 * Method:    nativeGauss2d
 * Signature: (J)[D
 */
JNIEXPORT jdoubleArray JNICALL Java_net_zigzak_androidcalcpi_NativeRNG_nativeGauss2d
  (JNIEnv *, jobject, jlong);

/*
 * Class:     net_zigzak_androidcalcpi_NativeRNG
 * Method:    nativeClose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_net_zigzak_androidcalcpi_NativeRNG_nativeClose
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
