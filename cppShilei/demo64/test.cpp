#include <functional>
#include <iostream>
#include <memory>

using namespace std;

template <typename T>
class MyDeletor {
   public:
    void operator()(T* ptr) const {
        cout << "call MyDeletor.operator()" << endl;
        delete[] ptr;
    }
};

template <typename T>
class MyFileDeletor {
   public:
    void operator()(T* ptr) const {
        cout << "call MyFileDeletor.operator()" << endl;
        fclose(ptr);
    }
};

int main() {
    unique_ptr<int, MyDeletor<int>> ptr1(new int[100]);
    unique_ptr<FILE, MyFileDeletor<FILE>> ptr2(fopen("data.txt", "w"));

    // lambda表达式 -》函数对象 function
    unique_ptr<int, function<void(int*)>> ptr3(new int[100], [](int* p) {
        cout << "call lambda release new int[100]" << endl;
        delete[] p;
    });

    unique_ptr<FILE, function<void(FILE*)>> ptr4(
        fopen("data.txt", "w"), [](FILE* p) {
            cout << "call lambda release new fopen" << endl;
            fclose(p);
        });

    return 0;
}