#include <cstddef>
#include <stdexcept>
#include <dlfcn.h>  // non-NDK library
#define SHA256_DIGEST_LENGTH 32

#include <jni.h>
#include <bits/ios_base.h>
#include <sstream>
#include <iomanip>
#include <iostream>


#include "net_zigzak_androidcalcpi_NativeEncrypt.h"
#include "util.hpp"

using namespace std;

namespace {
    template<typename T>
    void dlsym_cast(T& ptr, const char *name) {
        void* addr = dlsym(RTLD_DEFAULT, name);
        ptr = reinterpret_cast<T>(reinterpret_cast<size_t>(addr));
    }
} // anonymous namespace

// declare relevant structs and types
typedef struct SHA256state_st {
    unsigned int data[28];
} SHA256_CTX;

JNIEXPORT jstring JNICALL
Java_net_zigzak_androidcalcpi_NativeEncrypt_nativeEncrypt(JNIEnv *env, jclass type, jstring message_) {
    ENTER()
    const char *message = env->GetStringUTFChars(message_, 0);

    SHA256_CTX ctx;
    int (*SHA224_Init)(SHA256_CTX *); // function pointer
    int (*SHA256_Update)(SHA256_CTX *, const void *, size_t);
    int (*SHA256_Final)(unsigned char *, SHA256_CTX *);

    LOG("Loading functions")
    dlsym_cast(SHA224_Init, "SHA224_Init");
    dlsym_cast(SHA256_Update, "SHA256_Update");
    dlsym_cast(SHA256_Final, "SHA256_Final");

    unsigned char output[SHA256_DIGEST_LENGTH];

    LOG("Initialize")
    SHA224_Init(&ctx);
    LOG("Encrypt")
    SHA256_Update(&ctx, static_cast<const void *>(message), env->GetStringLength(message_));
    LOG("Final")
    SHA256_Final(output, &ctx);

    LOG("Release string")
    env->ReleaseStringUTFChars(message_, message);

    ostringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << "0x" << hex << setw(2) << (int)output[i];
    }
    LOG("Return")
    return env->NewStringUTF(ss.str().c_str());
}