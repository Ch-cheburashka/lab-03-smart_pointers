# Laboratory Work №3

This laboratory work is designed for students to study basic data structures.

## Theoretical Background

To better understand the operation of this "smart" pointer, you need to implement it yourself.

### Task 1

**UniquePtr** implements a smart pointer that is the sole owner of an object. When a **UniquePtr** is deleted, it frees the resource it points to.

```c++
template <typename T>
class UniquePtr {
public:
    UniquePtr();
    UniquePtr(T* ptr);
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& other);
    UniquePtr& operator=(const UniquePtr&) = delete;
    UniquePtr& operator=(UniquePtr&& other);
    ~UniquePtr();
    
    // Checks if the pointer points to an object
    operator bool() const;
    auto operator*() const -> T&;
    auto operator->() const -> T*;
    
    auto get() -> T*;
    void reset();
    void reset(T* ptr);
    void swap(UniquePtr& other);
};

template <typename Args...>
auto makeUnique(Args&&... args) -> UniquePtr<T>;
```

### Task 2

**SharedPtr** implements reference counting for a resource. The resource will be freed when the reference count drops to 0. This system implements one of the core rules of garbage collection.

```c++
template <typename T>
class SharedPtr {
public:
    SharedPtr();
    SharedPtr(T* ptr);
    SharedPtr(const SharedPtr& r);
    SharedPtr(SharedPtr&& r);
    ~SharedPtr();
    auto operator=(const SharedPtr& r) -> SharedPtr&;
    auto operator=(SharedPtr&& r) -> SharedPtr&;

    operator bool() const;
    auto operator*() const -> T&;
    auto operator->() const -> T*;
    
    auto get() -> T*;
    void reset();
    void reset(T* ptr);
    void swap(SharedPtr& r);
    // Returns the number of SharedPtr instances that point to the same managed object
    auto use_count() const -> size_t;
};

template <typename Args...>
auto makeShared(Args&&... args) -> SharedPtr<Args...>;
```

