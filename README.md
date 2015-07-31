# AndroidCalcPi

This is a simple Android project to play with C++ and test Android Studio 1.3 and Gradle 2.5. Moreover, it is part of my [tutorials](http://www.slideshare.net/geisshirt/tips-and-tricks-for-building-high-performance-android-apps-using-native-code) and [talk](http://www.slideshare.net/geisshirt/building-high-performance-android-applications-in-java-and-c?related=1) on how to use C++ in Android.

The following branches exist:

* `master` has all except benchmarking code.

* `initial` is where you begin. It is an empty app (for Android Studio 1.3 and Gradle 2.5) and some C++ code. The C++ code acts as the "legacy" code for the exercises.

* `wrapping` implements the wrapper classes and intermediate C++ code so the "legacy" code can be used in an Android app.

* `reducing-size` adds compiler and linker flags to reduce the sizes of the final `.so` files.

* `exceptions-and-logging` is about rethrowing C++ exceptions as Java exceptions. Furthermore, the introduction of logging through the Android logging mechanism is also found here.

* `posix-threads` shows how to use POSIX threads in Android native code. It requires a larger refactoring in order to get a thread-safe random number generator.

* `non-ndk-libraries` can be used to get you started using some of the libraries on Android devices but not included in NDK.

* `benchmarking` adds a bit of benchmarking. It hasn't been merged into `master` as the runs are too short to give any reliable results.

You are welcome to try out the code and open Github issues.