#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

void print_hello()
{
    cout << "hello word!" << endl;
}

int main()
{
    thread t(print_hello);

    t.join();

    return 0;
}