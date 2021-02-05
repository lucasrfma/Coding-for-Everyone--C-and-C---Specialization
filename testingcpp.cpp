#include <iostream>
#include <complex>

using namespace std;

const int size = 5;

template <class T>
inline T sum(T *array, int length){
    T sum = 0;
    for(length--; length >=0 ; length--)
        sum += array[length];
    return sum;
}

template <class S>
inline void swap2(S& q, S& r){
    S temp = q;
    q = r;
    r = temp;
}

int main(){

    // std::cout << sizeof(short) << " " << sizeof(int) << " " << sizeof(long) << " " << sizeof(long long) << std::endl;
    // printf("%d %d %d %d\n",sizeof(short),sizeof(int),sizeof(long),sizeof(long long));

    int ints[size] = {1,2,3,4,5};
    double doubles[size] = {1.5,2.5,3.5,4.5,5.5};
    complex<double> comp1(1.0,1.5), comp2(2.0,2.5);

    
    cout << endl << "Sum of Ints: " << sum(ints,size) << endl;
    cout <<         "Sum of Doubs: " << sum(doubles,size) << endl;

    cout << "Comp1 = " << comp1 << endl;
    cout << "Comp2 = " << comp2 << endl <<
         "---Swapping---" << endl;
    swap2(comp1,comp2);
    cout << "Comp1 = " << comp1 << endl;
    cout << "Comp2 = " << comp2 << endl;
    cout << "Sum =  " << comp1 + comp2 << endl;
    cout << "product =  " << comp1 * comp2 << endl;

    return 0;
} 
