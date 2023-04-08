//
// Created by teufel on 21.01.23.
//

#ifndef LAB_03_SMART_POINTERS_SHAREDPTR_HPP
#define LAB_03_SMART_POINTERS_SHAREDPTR_HPP

template<typename T>
class SharedPtr {
public:
    SharedPtr();

    SharedPtr(T *ptr);

    SharedPtr(const SharedPtr &r);

    SharedPtr(SharedPtr &&r);

    ~SharedPtr();

    auto operator=(const SharedPtr &r) -> SharedPtr &;

    auto operator=(SharedPtr &&r) -> SharedPtr &;

    // проверяет, указывает ли указатель на объект
    operator bool() const;

    auto operator*() const -> T &;

    auto operator->() const -> T *;

    auto get() -> T *;

    void reset();

    void reset(T *ptr);

    void swap(SharedPtr &r);

    // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t;
};

// Необходимо будет объяснить, что это за функция и для чего она была реализована
template<typename Args...>
auto makeShared(Args &&... args) -> SharedPtr<Args...>;

#endif //LAB_03_SMART_POINTERS_SHAREDPTR_HPP
