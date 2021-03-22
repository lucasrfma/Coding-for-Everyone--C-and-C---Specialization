#include <iostream>

using std::cout;
using std::endl;
using std::string;

void testValue(int&& a)
{
    cout << &a << endl;
}

void testString(const string& str)
{
    cout << "Hello, my name is " << str << endl;
    cout << "String address: " << &str << endl;
}

int main(int argc, char const *argv[])
{
    int i = 0;

    testValue(std::move(i));
    testValue(10);

    string name1, name2;

    cout << "String address: " << &name1 << endl;
    testString(name1);
    cout << "String address: " << &name2 << endl;
    testString(name2);
    name1+=name2;
    cout << "String address: " << &name1 << endl;
    testString(name1);
    testString("Lucas");

    return 0;
}
