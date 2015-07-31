// compile: clang++ -o test -Iapp/src/main/jni test.cpp app/src/main/jni/pi.cpp app/src/main/jni/RNG.cpp
// run: ./test 50000

#include <iostream>
#include <cstdlib>
#include "pi.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Wrong number of arguments." << std::endl;
        exit(-1);
    }
    std::size_t iterations = atoi(argv[1]);

    Pi *pi = new Pi(iterations);
    std::cout.unsetf (std::ios::floatfield);
    std::cout.precision(10);
    std::cout << "pi = " << pi->estimate() << std::endl;
}
