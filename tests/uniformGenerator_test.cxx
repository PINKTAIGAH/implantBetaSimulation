#include <iostream>
#include "UniformGenerator.hh"

int main() {
    UniformGenerator rng(0., 1.); // uniform in [0., 1.)

    for (int i = 0; i < 10; ++i) {
        std::cout << rng.Generate() << std::endl;
    }

    rng.SetRange(0., 3.5); // uniform in [0. 3.5)

    std::cout << "Changed range to [0., 3.5) " << std::endl;

    for (int i = 0; i < 10; ++i) {
        std::cout << rng.Generate() << std::endl;
    }

    return 0;
}