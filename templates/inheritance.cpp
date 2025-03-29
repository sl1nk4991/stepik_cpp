#include <cstddef>
#include <iostream>

struct ICloneable {
    virtual ICloneable* clone() const = 0;
    virtual ~ICloneable() = default;
};

template <typename T>
struct ValueHolder: ICloneable {
    ValueHolder(const T& value = T())
        : data_(value) {}

    ValueHolder* clone() const {
        return new ValueHolder(this->data_);
    }

    T data_;
};

struct S {
    S(int n = 0): n_(n) {};

    operator int() {
        return this->n_;
    }

private:
    //S& operator=(const S& other);

    int n_ = 0;
};

class Any {
public:
    Any()
        : ptr_(nullptr) {}

    template <typename T>
    Any(const T object)
        : ptr_(new ValueHolder<T>(object)) {}

    ~Any() {
        delete this->ptr_;
        this->ptr_ = nullptr;
    }

    Any(const Any& other)
        :ptr_(other.ptr_ ? other.ptr_->clone() : nullptr) {}

    Any& operator=(const Any& other) {
        if (this != &other) {
            delete this->ptr_;
            this->ptr_ = other.ptr_ ? other.ptr_->clone() : nullptr;
        }

        return *this;
    }

    template <typename T>
    Any& operator=(const T& other) {
        delete this->ptr_;
        this->ptr_ = new ValueHolder<T>(other);

        return *this;
    }

    template <typename T>
    T* cast() {
        ValueHolder<T>* ptr =  dynamic_cast<ValueHolder<T>*>(this->ptr_);

        if (ptr) {
            return &ptr->data_;
        } else {
            return nullptr;
        }
    }

private:
    ICloneable *ptr_ = nullptr;
};

int main(void) {
    std::cout << "iostream used" << std::endl;

    Any empty;

    Any i{10};

    std::cout << empty.cast<int>() << std::endl;
    std::cout << empty.cast<std::nullptr_t>() << std::endl;

    std::cout << i.cast<int>() << std::endl;
    std::cout << i.cast<float>() << std::endl;

    Any d{i};
    empty = d;
    empty = 0;

    std::cout << d.cast<int>() << std::endl;
    std::cout << d.cast<float>() << std::endl;

    return 0;
}
