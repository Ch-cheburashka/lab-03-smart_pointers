# Лабораторная работа №3

Данная лабораторка предназначена для того, чтобы студенты отдохнули от прошлых лаб и изучили базовые структуры данных

## Теоретическая справка

Чтобы лучше усвоить и понять принцип работы этого "умного" указателя, необходимо его реализовать своими руками

TODO: Добавить теоретическую справку

Кстати проект ```CMakeLists.txt``` надо будет реализовать самому :)

### Задание 1

**UniquePtr** реализует умный указатель, который является единственным владельцем объекта. При удалении **UniquePtr** освобождает ресурс, на который он указывает.

Реализуйте шаблонный класс `UniquePtr`:

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
    
    // проверяет, указывает ли указатель на объект
    operator bool() const;
    auto operator*() const -> T&;
    auto operator->() const -> T*;
    
    auto get() -> T*;
    void reset();
    void reset(T* ptr);
    void swap(UniquePtr& other);
};

// Необходимо будет объяснить, что это за функция и для чего она была реализована
template <typename Args...>
auto makeUnique(Args&&... args) -> UniquePtr<T>;
```

### Задание 2

**SharedPtr** реализует подсчет ссылок на ресурс. Ресурс освободится тогда, когда счетчик ссылок на него будет равен 0. Как видно, система реализует одно из основных правил сборщика мусора.
 Например, класс `scoped_refptr` (аналог `std::shared_ptr`) используется в Chromium [32,753 раз](https://cs.chromium.org/search/?q=scoped_refptr&sq=package:chromium&type=cs).

Реализуйте шаблон класса `SharedPtr`. Для счетчика ссылок используйте переменную класса `std::atomic_uint`. Интерфейс работы с этим классом аналогичен работе с переменной типа `unsigned int`, т.е. к нему применимы операции префиксного инкремента и декремента.

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

    // проверяет, указывает ли указатель на объект
    operator bool() const;
    auto operator*() const -> T&;
    auto operator->() const -> T*;
    
    auto get() -> T*;
    void reset();
    void reset(T* ptr);
    void swap(SharedPtr& r);
    // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t;
};

// Необходимо будет объяснить, что это за функция и для чего она была реализована
template <typename Args...>
auto makeShared(Args&&... args) -> SharedPtr<Args...>;
```

### Рекомендации
Подробное объяснение об устройстве `shared_ptr` можно прочитать в книге "Эффективный и современный С++" Скотта Мейерса или на соответсвующей лекции по Алгоритмическим Языкам.

### Вопросы, на которые нужно уметь ответить
* Что такое умный указатель?
* Какие проблемы решают умные указатели?
* Какие типы умных указателей вы знаете?
* Какие преимущества и недостатки умных указателей?
* Для чего реализованы методы `makeUnique` и `makeShared`?
