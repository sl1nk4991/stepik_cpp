#include <iostream>
#include <cstring>
#include <optional>

struct String {
    String(const char *str = "", std::optional<std::size_t> size = std::nullopt)
        : size(size.value_or(strlen(str))),
        str(new char[this->size + 1]) {
            strncpy(this->str, str, this->size);
            this->str[this->size] = 0;
        }

    String(const String &other)
        : String(other.str) {}

    String(String &&other)
        : size(other.size), str(other.str) {
            other.size = 0;
            other.str = nullptr;
        }

    ~String() {
        delete [] str;
    }

    String &operator=(const String &other) {
        if (this != &other) {
            this->size = other.size;
            char *tmp = new char[this->size + 1];
            strcpy(tmp, other.str);
            delete [] this->str;
            this->str = tmp;
        }

        return *this;
    }

    String &operator=(String &&other) {
        if (this != &other) {
            this->size = other.size;
            delete [] this->str;
            this->str = other.str;
            other.size = 0;
            other.str = nullptr;
        }

        return *this;
    }

    struct SubString {
        SubString(char *str, std::size_t i)
            : index(i), str(str) {}

        String operator[](std::size_t i) const {
            return String(this->str, i - index);
        }

        std::size_t index;
        char *str;
    };

    SubString operator[] (std::size_t i) const {
        return SubString(this->str + i, i);
    }

    friend std::ostream& operator<<(std::ostream &os, String const &other) {
        return os << other.str;
    }

    operator const char*() const {
        return this->str;
    }

    const char *get_str() const {
        return this->str;
    }

    void operator+=(const String &other) {
        this->append(other);
    }

    void append(const String &other) {
        char *tmp = new char[this->size + other.size + 1];
        strcpy(tmp, this->str);
        strcpy(tmp + this->size, other.str);
        this->size += other.size;
        delete [] this->str;
        this->str = tmp;
    }

    std::size_t size;
    char *str;
};



int main(void) {
    std::cout << "iostream used" << std::endl;

    String const s1("hello");
    String const s2 = s1[0][4];
    String const s3 = s1[1][4];

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;

    return 0;
}
