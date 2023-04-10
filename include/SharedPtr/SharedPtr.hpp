#ifndef LAB_03_SMART_POINTERS_SHAREDPTR_HPP
#define LAB_03_SMART_POINTERS_SHAREDPTR_HPP

template<typename T>
class SharedPtr {
public:
    SharedPtr() : _ptr(nullptr), _count(nullptr) {}

    explicit SharedPtr(T *ptr) : _ptr(ptr), _count(new size_t(1)) { }

    SharedPtr(const SharedPtr &r) : _ptr(r._ptr), _count(r._count) {
        ++*_count;
    }

    SharedPtr(SharedPtr &&r) noexcept : _ptr(r._ptr), _count(r._count) {
        r._ptr = nullptr;
        r._count = nullptr;
    }

    ~SharedPtr() {
        if (*_count > 1)
            --*_count;
        else {
            delete _ptr;
            delete _count;
        }
    }

    auto operator=(const SharedPtr &r) -> SharedPtr & {
        _ptr = r._ptr;
        _count = r._count;
        ++*_count;
        return *this;
    }

    auto operator=(SharedPtr &&r)  noexcept -> SharedPtr & {
        _ptr = r._ptr;
        _count = r._count;
        r._count = nullptr;
        r._ptr = nullptr;
        return *this;
    }

    explicit operator bool() const {
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
        if (*_count == 1) {
            delete _ptr;
            _ptr = ptr;
        }
        else {
            _ptr = ptr;
            *_count = 1;
        }
    }

    void swap(SharedPtr &r) {
        if (_ptr != r._ptr) {
            std::swap(_ptr, r._ptr);
            std::swap(_count, r._count);
        }
    }

    auto use_count() const -> size_t {
        return *_count;
    }

private:
    T* _ptr;
    size_t* _count;
};

// Необходимо будет объяснить, что это за функция и для чего она была реализована
template<typename ...Args>
auto makeShared(Args &&... args) -> SharedPtr<Args...>;

#endif //LAB_03_SMART_POINTERS_SHAREDPTR_HPP
