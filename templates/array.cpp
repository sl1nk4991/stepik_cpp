#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <utility>

template <typename T>
class Array
{
public:
    // Список операций:
    Array() = default;

    explicit Array(std::size_t size, const T& value = T()) noexcept
        :size_(size),
        data_(reinterpret_cast<T*>(new char[this->size_ * sizeof(T)])) {
        //std::fill(this->data_, this->data_ + this->size_, value);
        for (size_t i = 0; i < this->size_; i++)
            new (&this->data_[i]) T(value);
    }
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.

    Array(const Array<T> &other) noexcept
        :size_(other.size_),
        data_(reinterpret_cast<T*>(new char[this->size_ * sizeof(T)])) {
            //std::copy(other.data_, other.data_ + other.size_, this->data_);
            for (size_t i = 0; i < this->size_; i++) {
                new (&this->data_[i]) T(other.data_[i]);
            }
    }
    //   конструктор копирования, который создает
    //   копию параметра. Считайте, что для типа
    //   T определен оператор присваивания.

    ~Array() noexcept {
        for (size_t i = 0; i < this->size_; i++) {
            this->data_[i].~T();
        }

        delete [] reinterpret_cast<char*>(this->data_);
    }
    //   деструктор, если он вам необходим.

    Array<T>& operator=(const Array<T> &other) noexcept {
        if (this != &other) {
            Array<T> temp(other);
            std::swap(this->size_, temp.size_);
            std::swap(this->data_, temp.data_);
        }
        return *this;
    }
    //   оператор присваивания.

    std::size_t size() const noexcept {
        return this->size_;
    }
    //   возвращает размер массива (количество
    //                              элементов).

    T& operator[](std::size_t n) {
#ifndef NDEBUG
        assert(n < this->size_ && "Index out of bounds");
#endif
        if (n >= this->size_) {
            throw std::out_of_range("Index out of bounds");
        }

        return this->data_[n];
    }

    const T& operator[](std::size_t n) const {
#ifndef NDEBUG
        assert(n < this->size_ && "Index out of bounds");
#endif
        if (n >= this->size_) {
            throw std::out_of_range("Index out of bounds");
        }

        return this->data_[n];
    }
    //   две версии оператора доступа по индексу.

    T* begin() {
        return this->data_;
    }

    T* end() {
        return this->data_ + size_;
    }

private:
    std::size_t size_ = 0;
    T *data_ = nullptr;
};

struct S {
    S(const char *str = "",
            std::optional<std::size_t> n = std::nullopt)
        : len_(n.value_or(strlen(str))), str_(new char[this->len_ + 1]) {
            strncpy(this->str_, str, this->len_ + 1);
#ifdef EBUG
            std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        }

    ~S() {
        delete [] this->str_;
    }

    S(const S& other)
        : len_(other.len_), str_(new char[this->len_ + 1]) {
            strncpy(this->str_, other.str_, this->len_ + 1);
#ifdef EBUG
            std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
    }

    S(S&& other) noexcept
        : len_(std::exchange(other.len_, 0)),
        str_(std::exchange(other.str_, nullptr)) {
#ifdef EBUG
            std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        }

    S& operator=(const S& other) {
#ifdef EBUG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        //if (this != &other) {
        //    S temp(other);
        //    std::swap(this->str_, temp.str_);
        //    std::swap(this->len_, temp.len_);
        //}
        //return *this;

        return *this = S(other);
    }

    S& operator=(S&& other) noexcept {
#ifdef EBUG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        if (this != &other) {
            std::swap(this->str_, other.str_);
            std::swap(this->len_, other.len_);
        }

        return *this;
    }

    //friend std::ostream& operator<<(std::ostream &os, const S &other) {
    //    return os << other.str_;
    //}

    operator char*() {
        return this->str_;
    }

private:
    std::size_t len_ = 0;
    char *str_ = nullptr;
};

template <typename T, class Comp>
T minimum(Array<T>& array, Comp comp) {
    T *tmp = &array[0];
    for (size_t i = 1; i < array.size(); i++) {
        if (comp(array[i], *tmp)) {
            *tmp = array[i];
        }
    }
    return *tmp;
}

bool less(int a, int b) { return a < b; }
struct Greater { bool operator()(int a, int b) const {return b < a; } };

template <typename T>
void flatten(const Array<T>& array, std::ostream& other) {
    for (size_t i = 0; i < array.size(); i++) {
        other << array[i] << " ";
    }
    other << std::endl;
}

template <typename T>
void flatten(const Array<Array<T>>& array, std::ostream& other) {
    for (size_t i = 0; i < array.size(); i ++) {
        flatten(array[i], other);
    }
}

int main(void) {
    std::cout << "iostream used" << std::endl;

    Array<int> ints{2, 0};
    ints[0] = 10;
    ints[1] = 20;
    flatten(ints, std::cout);

    Array<Array<int>> array_of_ints{2, ints};
    flatten(array_of_ints, std::cout);

    Array<Array<Array<int>>> arrays{3, array_of_ints};
    flatten(arrays, std::cout);

    return 0;
}
