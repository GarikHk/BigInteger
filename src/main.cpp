#include <iostream>
#include "BigInteger.h"

int main() {
    // Initialize with an integer
    BigInteger a(123456789);

    // Initialize with a string from input
    BigInteger b;
    std::cin >> b;

    // Initialize from an array
    int arr[20] = {7, 1, 6, 1, 5, 5, 9, 0, 7, 3, 7, 0, 4, 4, 7, 6, 4, 4, 8, 1};
    BigInteger c(arr, 20, false);


    // Addition
    BigInteger sum = a + b;
    std::cout << "Sum: " << sum << std::endl;

    // Multiplication
    BigInteger product = a * b;
    std::cout << "Product: " << product << std::endl;

    // Division
    BigInteger quotient = b / a;
    std::cout << "Quotient: " << quotient << std::endl;

    return 0;

}
