#include <iostream>
#include <complex>

using namespace std;

template <class U>
inline void printArray(U *array,int size){
    for(int i = 0; i < size; i++){
        cout << array[i] << '\t';
    }
    cout <<endl;
}

template <class T1, class T2>
void copy(const T1 source[], T2 destination[], int size){
    for( int i = 0; i < size; i++){
        destination[i] = static_cast<T2>(source[i]);
        // destination[i] = (T2)(source[i]);
    }
}

int main(){

    int intArray[] = {1,2,3,4,5};
    float floatArray[] = {2.0,3.5,4.99};
    char *stringArray[] = {"test one","testtwo"};

    printArray(intArray,5);
    printArray(floatArray,3);
    printArray(stringArray,2);

    copy(floatArray,intArray,3);

    printArray(intArray,5);

    return 0;
}