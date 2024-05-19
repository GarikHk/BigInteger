# BigInteger Class

The `BigInteger` class is a C++ implementation of an integer type, allowing the representation of integers of up to
100,000 digits. This class is useful for scenarios where integers larger than those supported by built-in
types (`int`, `long`, etc.) need to be handled, such as cryptography, mathematical calculations, and dealing with very
large numbers in general.


## Overview

This `BigInteger` class is a pet project assigned in university and is aimed at mastering C++ classes, and it is not 
recommended to be used in real life projects.


## How to Use

1. Include the BigInteger.h header file in your project.
2. Create BigInteger objects and perform arithmetic operations as needed.


## Features

- Supports arithmetic operations (addition, subtraction, multiplication, division) on integers of arbitrary size.
- Provides comparison operators (`<`, `<=`, `==`, `!=`, `>`, `>=`) for comparing `BigInteger` objects with integers or
  other `BigInteger` objects.
- Provides mathematical operators (`+`, `+=`, `-`, `-=`, `*`, `*=`, `/`, `/=`, `%`, `%=`, `^`) for common operations like
  addition, subtraction, multiplication, and division.
- Allows input and output operations via stream insertion (`<<`) and stream extraction (`>>`) operators.
- Handles both positive and negative numbers.
- Supports implicit conversion from `int` to `BigInteger` and vice versa.


## Usage

```cpp
#include <iostream>
#include "BigInteger.h"

int main() {
    // Initialize with an integer
    BigInteger a(123456789);

    // Initialize with a string from input
    BigInteger b;
    cin >> b;

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
```


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
