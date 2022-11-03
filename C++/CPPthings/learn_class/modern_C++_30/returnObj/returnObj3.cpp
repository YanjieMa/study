//
// Created by light on 19-12-22.
//


#include <iostream>

using namespace std;

// Can copy and move
class A {
public:
    A() { cout << "Create A\n"; }

    ~A() { cout << "Destroy A\n"; }

    A(const A &) { cout << "Copy A\n"; }

    A(A &&) { cout << "Move A\n"; }

    A& operator=(const A&a)
    {
        std::cout << "copy assignment" << std::endl;
        return *this;
    }

    A& operator=(A &&a) {
        cout << "move assignment\n";
        return *this;
    }
};
// 编译器无法优化
A getA_duang() {
    A a1;
    A a2;
    if (rand() > 42) {
        return a1;
    }
    else {
        return a2;
    }
}

int main() {
//    cout<<"拷贝"<<endl;
//    auto a = getA_duang();

    cout<<"赋值"<<endl;
    A aa;
    aa=getA_duang();
}