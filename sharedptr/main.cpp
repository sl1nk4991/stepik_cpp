#include <iostream>

struct Expression {
    virtual double evaluate() const = 0;
    virtual ~Expression() = default;
};

struct Number: Expression {
    Number(double number = 0)
        :number_(number) {}

    ~Number() = default;

    double evaluate() const {
        return this->number_;
    };

private:
    double number_;
};

struct BinaryOperation: Expression {};

struct SharedPtr {
    explicit SharedPtr(Expression *ptr = 0)
        : ptr_(ptr),
        count(this->ptr_ != nullptr ? new std::size_t{1} : nullptr) {}

    ~SharedPtr() {
        if (this->ptr_ != nullptr) {
            (*this->count)--;

            if (*this->count == 0) {
                delete this->ptr_;
                this->ptr_ = nullptr;
                delete this->count;
                this->count = nullptr;
            }
        }
    }

    SharedPtr(const SharedPtr &other)
        : ptr_(other.ptr_), count(other.count) {
            if (this->ptr_ != nullptr) {
                (*this->count)++;
            }
    }

    SharedPtr& operator=(const SharedPtr &other) {
        if (this != &other) {
            this->~SharedPtr();
            new (this) SharedPtr(other);

            //this->ptr_ = other.ptr_;
            //if (other.ptr_ != nullptr) {
            //    this->count = other.count;
            //    (*this->count)++;
            //}
        }

        return *this;
    }

    Expression* get() const {
        return this->ptr_;
    }

    void reset(Expression *ptr = 0) {
        //this->~SharedPtr();
        *this = SharedPtr(ptr);
    }

    Expression& operator*() const {
        return *this->ptr_;
    }

    Expression* operator->() const {
        return this->ptr_;
    }

    operator Expression*() const {
        return this->ptr_;
    }

private:
    Expression *ptr_ = nullptr;
    std::size_t *count = nullptr;
};

#ifndef TEST
int main(void) {
    std::cout << "iostream used" << std::endl;

    SharedPtr p1;
    {
        SharedPtr p2(new Number(5));
        SharedPtr p3(new Number(10));
        SharedPtr p4(p2);
        SharedPtr p5;
        p5 = p2;
        p5 = p4;
        p1 = p5;
        p3.reset(nullptr);
        p3 = p5;
        p5.reset(nullptr);
        SharedPtr p6;
        SharedPtr p7;
        p7 = p7;
        p7.reset(nullptr);
        p7.reset(new Number(15));
        SharedPtr p8(new Number(20));
        p8.reset(nullptr);
    }
    p1 = p1;

    std::cout << p1 << std::endl;

    return 0;
}
#endif
