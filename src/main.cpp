#include <iostream>
#include "BigInteger.h"

int main() {
    BigInteger a(2);

    int arr1[20] = {8, 8, 4, 9, 1, 9, 9, 9, 3, 0, 5, 3, 5, 1, 5, 5, 2, 3, 0, 1};
    BigInteger b(arr1, 20, true);

    int arr[20] = {7, 1, 6, 1, 5, 5, 9, 0, 7, 3, 7, 0, 4, 4, 7, 6, 4, 4, 8, 1};
    BigInteger c(arr, 20, false);

    a ^= 5;

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;

    return 0;
}
