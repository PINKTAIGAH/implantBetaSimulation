#include <iostream>
#include <DiscreteGenerator.hh>

int main() {
    DiscreteGenerator rng(1, 256); // discrete uniform in [1, 256]
    for (int i = 0; i < 10; ++i) {
        std::cout << rng.Generate() << std::endl;
    }

    rng.SetRange(0, 3); // uniform in [0 3]

    std::cout << "Changed range to [0., 3] " << std::endl;

    for (int i = 0; i < 10; ++i) {
        std::cout << rng.Generate() << std::endl;
    }

    return 0;
}