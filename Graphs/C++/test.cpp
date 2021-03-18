#include <iostream>

using std::cout;
using std::endl;

void testValue(int&& a)
{
    cout << &a << endl;
}

int main(int argc, char const *argv[])
{
    int i = 0;

    testValue(std::move(i));
    testValue(10);

    int b = 5;
    cout << &i;

    return 0;
}
