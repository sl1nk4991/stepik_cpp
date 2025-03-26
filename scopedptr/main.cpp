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

struct ScopedPtr
{
    explicit ScopedPtr(Expression *ptr = 0)
        :ptr_(ptr) {}

    ~ScopedPtr() {
        delete this->ptr_;
    }

    Expression* get() const {
        return this->ptr_;
    }

    Expression* release() {
        Expression *ret = this->ptr_;
        this->ptr_ = nullptr;
        return ret;
    }

    void reset(Expression *ptr = 0) {
        delete this->ptr_;
        this->ptr_ = ptr;
    }

    Expression& operator*() const {
        return *this->ptr_;
    }

    Expression* operator->() const {
        return this->ptr_;
    }


private:
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};

int main(void) {
    std::cout << "iostream used" << std::endl;

    Expression *num = new Number{5};

    ScopedPtr num_ptr{num};

    std::cout << (*num_ptr).evaluate() << std::endl;

    return 0;
}
