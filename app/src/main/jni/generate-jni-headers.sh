#!/bin/bash
#
# Generate header file for JNI calls
#
# Assumption: the .java files have been compiled
# 1. build project using Android Studio (or gradle); unit tests will probably fail due to missing native methods
# 2. run this script

# Setting up
CLASSDIR="$(pwd)/../../../../app/build/intermediates/classes/all/debug"
JNIDIR="$(pwd)"

# Generate the headers
(cd "$CLASSDIR" && javah -jni -classpath "$CLASSDIR" -d "$JNIDIR" net.zigzak.androidcalcpi.NativeEncrypt net.zigzak.androidcalcpi.NativePi net.zigzak.androidcalcpi.NativeRNG)

# Remove "empty" header files (they have 13 lines)
wc -l "$JNIDIR"/*.h | grep " 13 " | awk '{print $2}' | xargs rm -f
