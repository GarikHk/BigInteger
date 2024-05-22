#include <iostream>
#include "BigInteger.h"

BigInteger fibonacci(int n) {
    if (n < 1)
        throw std::runtime_error("Number of terms must be at least 1.");

    BigInteger f1(0);
    BigInteger f2(1);
    BigInteger sum;

    n--;
    while (n--) {
        sum = f1 + f2;
        f1 = f2;
        f2 = sum;
    }

    return sum;
}

BigInteger factorial(int n) {
    BigInteger f(1);
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}

int main() {
    // Initialize with an integer
    BigInteger a(123456789);

    // Initialize with a string from input
    BigInteger b;
    std::cout << "Enter a big integer: ";
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

    // Sum of Fibonacci sequences
    int x = 100;
    std::cout << "Fibonacci of the " << x << " the sequence: " << fibonacci(x) << "\n"; // 354,224,848,179,261,915,075

    // Factorial of the nth number
    int y = 20;
    std::cout << "Factorial of the " << y << "th : " << factorial(y) << "\n";           // 2,432,902,008,176,640,000

    return 0;
}
