//
// Created by teufel on 21.01.23.
//

#ifndef LAB_03_SMART_POINTERS_UNIQUEPTR_HPP
#define LAB_03_SMART_POINTERS_UNIQUEPTR_HPP

template<typename T>
class UniquePtr {
public:
    UniquePtr();

    UniquePtr(T *ptr);

    UniquePtr(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&other);

    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr &operator=(UniquePtr &&other);

    ~UniquePtr();

    // проверяет, указывает ли указатель на объект
    operator bool() const;

    auto operator*() const -> T &;

    auto operator->() const -> T *;

    auto get() -> T *;

    void reset();

    void reset(T *ptr);

    void swap(UniquePtr &other);
};

// Необходимо будет объяснить, что это за функция и для чего она была реализована
template<typename Args...>
auto makeUnique(Args &&... args) -> UniquePtr<T>;

#endif //LAB_03_SMART_POINTERS_UNIQUEPTR_HPP
