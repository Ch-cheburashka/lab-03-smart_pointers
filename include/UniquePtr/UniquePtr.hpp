#ifndef LAB_03_SMART_POINTERS_UNIQUEPTR_HPP
#define LAB_03_SMART_POINTERS_UNIQUEPTR_HPP

#include <iostream>

template<typename T>
class UniquePtr {
public:
    UniquePtr() : _ptr(nullptr) {}

    explicit UniquePtr(T *ptr) : _ptr(std::move(ptr)) {}

    UniquePtr(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&other) noexcept {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }

    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr &operator=(UniquePtr &&other) noexcept {
        _ptr = other._ptr;
        other._ptr = nullptr;
        return *this;
    }

    ~UniquePtr() {
        delete _ptr;
    }

    operator bool() const {
        return _ptr != nullptr;
    }

    auto operator*() const -> T & {
        return *_ptr;
    }

    auto operator->() const -> T * {
        return _ptr;
    }

    auto get() -> T * {
        return _ptr;
    }

    void reset() {
        _ptr = nullptr;
    }

    void reset(T *ptr) {
        delete _ptr;
        _ptr = ptr;
    }

    void swap(UniquePtr &other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }
private:
    T * _ptr;
};

// Необходимо будет объяснить, что это за функция и для чего она была реализована
template<typename ...Args>
auto makeUnique(Args &&... args)-> UniquePtr<Args...>;

#endif //LAB_03_SMART_POINTERS_UNIQUEPTR_HPP
