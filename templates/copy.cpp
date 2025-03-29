#include <cstddef>
#include <cstdlib>
#include <iostream>

template<typename T, typename U>
void copy_n(T* to, U* from, std::size_t n) {
    while (n--) {
        *to++ = static_cast<T>(*from++);
    }
}

int main() {
    std::cout << "iostream used" << std::endl;

    int ints[] = {1, 2, 3, 4};
    double doubles[4] = {};
    copy_n(doubles, ints, 4);

    for (auto &i: ints) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (auto &i: doubles) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
