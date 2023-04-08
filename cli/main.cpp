#include <iostream>
#include <string>
#include <UniquePtr/UniquePtr.hpp>

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
        std::cout << "uniquePtr points to nullptr\n";
    else {
        std::cout << "uniquePtr:\n";
        std::cout << "test object: " << *u1 << "\n";
        std::cout << "name: " << u1->name << "\n";
    }

    if (!u2)
        std::cout << "uniquePtr1 points to nullptr\n\n";
    else {
        std::cout << "uniquePtr1:\n";
        std::cout << "test object: " << *u2 << "\n";
        std::cout << "name: " << u2->name << "\n\n";
    }
}

int main(int argc, char** argv) {

    std::cout << "creating uniquePtr pointing to test-object\n";
    UniquePtr<test> uniquePtr (new test{17,"Marie"});
    std::cout << "creating uniquePtr pointing to nullptr\n\n";
    UniquePtr<test> uniquePtr1;
    print_info(uniquePtr,uniquePtr1);

    std::cout << "reseting uniquePtr\n";
    uniquePtr.reset(new test{16,"Biba"});
    print_info(uniquePtr,uniquePtr1);

    std::cout << "swaping pointers\n";
    uniquePtr1.swap(uniquePtr);
    print_info(uniquePtr,uniquePtr1);

}