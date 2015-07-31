#include <stdexcept>
#include <sstream>

#include <jni.h>
#include <pthread.h>

#include "net_zigzak_androidcalcpi_NativePi.h"
#include "pi.hpp"
#include "util.hpp"

JNIEXPORT jlong JNICALL Java_net_zigzak_androidcalcpi_NativePi_nativeCreate
  (JNIEnv *env, jobject, jlong iterations, jlong generators)
{
    ENTER()
    try {
        LOG("iterations: %ld", S64(iterations))
        LOG("generators: %ld", S64(generators))
        Pi *pi = new Pi(static_cast<long>(iterations), static_cast<long>(generators));
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
    double estimate = pi->estimate(0);
    LOG("estimate = %e", estimate)
    return estimate;
}

JNIEXPORT void JNICALL Java_net_zigzak_androidcalcpi_NativePi_nativeClose
(JNIEnv *, jobject, jlong nativePtr) {
    ENTER_PTR(nativePtr)
    delete reinterpret_cast<Pi *>(nativePtr);
}

struct thread_info {
    pthread_t thread_id;
    int       thread_num;
    Pi       *pi;
};

static void *worker(void *arg)
{
    ENTER()
    double *estimate = static_cast<double *>(calloc(1, sizeof(double)));
    struct thread_info *tinfo = static_cast<struct thread_info *>(arg);
    Pi *pi = tinfo->pi;

    LOG("estimate")
    estimate[0] = pi->estimate(tinfo->thread_num);
    return static_cast<void *>(estimate);
}

JNIEXPORT jdouble JNICALL Java_net_zigzak_androidcalcpi_NativePi_nativeEstimateThread
        (JNIEnv *, jobject, jlong nativePtr, jlong numThreads)
{
    ENTER_PTR(nativePtr)
    Pi *pi = reinterpret_cast<Pi *>(nativePtr);
    size_t num_threads = static_cast<size_t>(numThreads);

    double estimate = 0.0;
    struct thread_info *tinfo = static_cast<struct thread_info *>(calloc(num_threads, sizeof(struct thread_info)));
    for(size_t i = 0; i < num_threads; ++i) {
        tinfo[i].thread_num = 0;
        tinfo[i].pi = pi;
        pthread_create(&tinfo[i].thread_id, NULL, &worker,(void *) &tinfo[i]);
    }
    for(size_t i = 0; i < num_threads; ++i) {
        void *res;
        pthread_join(tinfo[i].thread_id, &res);
        estimate += static_cast<double *>(res)[0];
        free(res);
    }
    estimate /= static_cast<double>(num_threads);
    LOG("estimate = %e", estimate)
    return estimate;
}