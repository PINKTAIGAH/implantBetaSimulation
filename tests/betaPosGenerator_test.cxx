#include <iostream>
#include "BetaPositionGenerator.hh"

int main() {
    BetaPositionGenerator rng;

    for (int i = 0; i < 10; ++i) {
        std::cout << rng.Generate() << std::endl;
    }

    return 0;
}