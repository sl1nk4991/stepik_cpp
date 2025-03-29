#include <iostream>

template <typename T, typename U>
struct SameType {
    static const bool value = false;
};

template <typename T>
struct SameType<T, T> {
    static const bool value = true;
};

struct Dummy {};
typedef int type;

int main() {
    std::cout << "iostream used" << std::endl;

    std::cout << SameType<int, int>::value << std::endl;
    std::cout << SameType<int, type>::value << std::endl;
    std::cout << SameType<int, int&>::value << std::endl;
    std::cout << SameType<Dummy, Dummy>::value << std::endl;
    std::cout << SameType<int, const int>::value << std::endl;

    return 0;
}
