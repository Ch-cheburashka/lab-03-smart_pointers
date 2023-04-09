#include <iostream>
#include <string>
#include <UniquePtr/UniquePtr.hpp>
#include <memory>
#include <vector>
struct test {
    int age;
    std::string name;
    friend std::ostream &operator<<(std::ostream &os,const test& test) {
        os << test.name << " - " << test.age;
        return os;
    }
};

void print_info (const UniquePtr<test>& u1, const UniquePtr<test>& u2) {
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

int main(int argc, char** argv) {

    std::cout << "creating u1 pointing to test-object\n";
    UniquePtr<test> u1 (new test{17, "Marie"});
    std::cout << "creating u1 pointing to nullptr\n\n";
    UniquePtr<test> u2;
    print_info(u1, u2);

    std::cout << "reseting u1\n";
    u1.reset(new test{16, "Biba"});
    print_info(u1, u2);

    std::cout << "swaping pointers\n";
    u2.swap(u1);
    print_info(u1, u2);

}