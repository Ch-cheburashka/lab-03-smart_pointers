#include <iostream>
#include <UniquePtr/UniquePtr.hpp>
#include <SharedPtr/SharedPtr.hpp>
struct test {
    int age;
    std::string name;
    test(int a, std::string n) : age(a), name(n) {}
    friend std::ostream &operator<<(std::ostream &os,const test& test) {
        os << test.name << " - " << test.age;
        return os;
    }
};

void print_unique_info (const UniquePtr<test>& u1, const UniquePtr<test>& u2) {
    if (!u1)
        std::cout << "u1 points to nullptr\n";
    else {
        std::cout << "u1:\n";
        std::cout << "test object: " << *u1 << "\n";
        std::cout << "name: " << u1->name << "\n";
    }

    if (!u2)
        std::cout << "u2 points to nullptr\n\n";
    else {
        std::cout << "u2:\n";
        std::cout << "test object: " << *u2 << "\n";
        std::cout << "name: " << u2->name << "\n\n";
    }
}

void print_shared_info (const SharedPtr<test>& s1, const SharedPtr<test>& s2) {
    if (!s1)
        std::cout << "s1 points to nullptr\n";
    else {
        std::cout << "s1:\n";
        std::cout << "counter " << s1.use_count() << "\n";
        std::cout << "test object: " << *s1 << "\n";
        std::cout << "name: " << s1->name << "\n";
    }

    if (!s2)
        std::cout << "s2 points to nullptr\n\n";
    else {
        std::cout << "s2:\n";
        std::cout << "counter " << s2.use_count() << "\n";
        std::cout << "test object: " << *s2 << "\n";
        std::cout << "name: " << s2->name << "\n\n";
    }
}

void test_unique () {
    std::cout << "creating u1 pointing to test-object\n";
    UniquePtr<test> u1 (new test{17, "Marie"});
    std::cout << "creating u1 pointing to nullptr\n\n";
    UniquePtr<test> u2;
    print_unique_info(u1, u2);

    std::cout << "reseting u1\n";
    u1.reset(new test{16, "Biba"});
    print_unique_info(u1, u2);

    std::cout << "swaping pointers\n";
    u2.swap(u1);
    print_unique_info(u1, u2);
}

void test_shared () {
    std::cout << "creating s1 pointing to test-object\n";
    auto s1 = makeShared<test>(17,"Marie");
    std::cout << "creating s1 pointing to the same test-object\n\n";
    SharedPtr<test> s2 (s1);
    print_shared_info(s1, s2);

    std::cout << "reseting s1\n";
    s1.reset(new test{16, "Biba"});
    print_shared_info(s1, s2);

    std::cout << "swaping pointers\n";
    s2.swap(s1);
    print_shared_info(s1, s2);
}

int main(int argc, char** argv) {
    test_shared();
}