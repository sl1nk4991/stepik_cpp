#include <iostream>

template <typename T, size_t n>
size_t array_size(const T (&)[n]) {
    return n;
}

int main() {
    std::cout << "iostream used" << std::endl;

    int ints[] = {1, 2, 3, 4};
    int *iptr = ints;
    double doubles[] = {3.14};

    std::cout << array_size(ints) << std::endl;
    std::cout << array_size(doubles) << std::endl;
    //std::cout << array_size(iptr) << std::endl;

    return 0;
}
