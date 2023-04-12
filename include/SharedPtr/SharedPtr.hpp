#ifndef LAB_03_SMART_POINTERS_SHAREDPTR_HPP
#define LAB_03_SMART_POINTERS_SHAREDPTR_HPP

template<typename T>
class SharedPtr {
public:
    SharedPtr() : _ptr(nullptr), _count(nullptr) {}

    explicit SharedPtr(T *ptr) : _ptr(ptr), _count(new size_t(1)) { }

    SharedPtr(const SharedPtr &r) {
        if (r._block != nullptr) {
            _block = r._block;
            ++_block->counter;
        }
        else {
            _ptr = r._ptr;
            _count = r._count;
            ++*_count;
        }
    }

    SharedPtr(SharedPtr &&r) noexcept {
        if (r._block != nullptr) {
            _block = r._block;
            r._block = nullptr;
        }
        else {
            _ptr = r._ptr;
            _count = r._count;
            r._count = nullptr;
            r._ptr = nullptr;
        }
    }

    ~SharedPtr() {
        if (_block != nullptr) {
            if (_block->counter > 1)
                --_block->counter;
            else
                delete _block;
        }
        else {
            if (_count != nullptr && *_count > 1)
                --*_count;
            else {
                delete _ptr;
                delete _count;
            }
        }
    }

    auto operator=(const SharedPtr &r) -> SharedPtr & {
        if (r._block != nullptr) {
            _block = r._block;
            ++_block->counter;
        }
        else {
            _ptr = r._ptr;
            _count = r._count;
            ++*_count;
        }
        return *this;
    }

    auto operator=(SharedPtr &&r)  noexcept -> SharedPtr & {
        if (r._block != nullptr) {
            _block = r._block;
            delete r._block;
        }
        else {
            _ptr = r._ptr;
            _count = r._count;
            r._count = nullptr;
            r._ptr = nullptr;
            return *this;
        }
        return *this;
    }

    explicit operator bool() const {
        return _ptr != nullptr || _block != nullptr;
    }

    auto operator*() const -> T & {
        if (_block != nullptr) {
            return _block->object;
        }
        return *_ptr;
    }

    auto operator->() const -> T * {
        if (_block != nullptr) {
            return &_block->object;
        }
        return _ptr;
    }

    auto get() -> T * {
        if (_block != nullptr) {
            return *_block->object;
        }
        return _ptr;
    }

    void reset() {
        if (_block != nullptr)
            _block = nullptr;
        else
            _ptr = nullptr;
    }

    void reset(T *ptr) {
        if (_block != nullptr) {
            if (_block->counter == 1) {
                delete _block;
                _block->counter = 1;
                _block->object = *ptr;
            }
            else {
                _block = nullptr;
                _ptr = ptr;
                _count = new size_t(1);
            }
        }
        else {
            if (*_count == 1) {
                delete _ptr;
                _ptr = ptr;
            } else {
                _ptr = ptr;
                *_count = 1;
            }
        }
    }

    void swap(SharedPtr &r) {
        if (r._block != nullptr) {
            if (_block != nullptr && _block != r._block) {
                std::swap(_block,r._block);
            }
            else {
                std::swap(_block,r._block);
                std::swap(_ptr,r._ptr);
                std::swap(_count,r._count);
            }
        }
        else {
            if (_ptr != nullptr && _ptr != r._ptr) {
                std::swap(_ptr, r._ptr);
                std::swap(_count, r._count);
            }
            else {
                std::swap(_block,r._block);
                std::swap(_ptr,r._ptr);
                std::swap(_count,r._count);
            }
        }
    }

    auto use_count() const -> size_t {
        if (_block != nullptr)
            return _block->counter;
        return *_count;
    }
private:
    template <typename U>
    struct control_block {
        size_t counter;
        U object;
    };

    T* _ptr = nullptr;
    size_t* _count = nullptr;
    control_block<T>* _block = nullptr;

    explicit SharedPtr(control_block<T>* storage_ptr) : _block(storage_ptr) {}

    template <typename U, typename ...Args>
    friend SharedPtr<U> makeShared(Args&& ...args);
};

template<typename U, typename... Args>
SharedPtr<U> makeShared(Args &&... args) {
    auto ptr = new typename SharedPtr<U>::template control_block<U>{1,U(std::forward<Args>(args)...)};
    return SharedPtr<U>(ptr);
}

#endif //LAB_03_SMART_POINTERS_SHAREDPTR_HPP
