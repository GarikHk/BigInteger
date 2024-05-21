#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include "BigInteger.h"

#define MAX 100000

using namespace std;

/**
 *
 * ~Constructors~
 *
 */
BigInteger::BigInteger() {
    _number_array[0] = 0;
    _length = 1;
    _positive = true;
}

BigInteger::BigInteger(int number) {
    _assign_integer(number);
}

BigInteger::BigInteger(const int *number_array, size_t length, bool positive = true) {
    _length = length;
    _positive = positive;

    for (size_t i = 0; i < _length; i++)
        _number_array[i] = number_array[i];
}

BigInteger::BigInteger(const BigInteger &big_int) {
    _assign(big_int);
}

BigInteger::~BigInteger() {
//    if (!_positive)
//        cout << '-';
//    for (int i = (int) _length - 1; i >= 0; i--)
//        cout << _number_array[i];
//    cout << " was destructured!\n";
}

/**
 *
 * ~Operators~
 *
 */
BigInteger &BigInteger::operator=(int number) {
    _assign_integer(number);
    return *this;
}

BigInteger &BigInteger::operator=(const BigInteger &big_int) {
    if (this == &big_int) return *this;
    _assign(big_int);
    return *this;
}

ostream &operator<<(ostream &out, const BigInteger &big_int) {
    if (!big_int._positive) {
        out << '-';
    }
    for (int i = (int) big_int._length - 1; i >= 0; i--) {
        out << big_int._number_array[i];
    }

//    out << "{\n\tnumber: ";
//    if (!big_int._positive)
//        out << '-';
//    for (int i = (int) big_int._length - 1; i >= 0; i--)
//        out << big_int._number_array[i];
//    out << ",\n\t_positive: "
//        << (big_int._positive ? "true" : "false")
//        << ",\n\t_length: "
//        << big_int._length
//        << ",\n\t_number_array: [";
//    for (int i = 0; i < big_int._length; i++)
//        out << big_int._number_array[i] << (i != big_int._length - 1 ? ", " : "]\n");
//    out << "}\n";

    return out;
}

istream &operator>>(istream &in, BigInteger &big_int) {
    string input;
    in >> input;
    size_t end = 0;
    big_int._length = input.length();
    big_int._positive = true;

    if (BigInteger::_is_sign(input[end])) {
        if (input[end] == 45) {
            big_int._positive = false;
        }
        big_int._length--;
        end++;
    }

    for (int i = 0; i < big_int._length; i++) {
        if (!isdigit(input[i + end])) {
            throw runtime_error("Enter a valid number");
        }

        int digit = input[i + end] - 48; // Turn the current digit into integer
        size_t index = big_int._length - 1 - i; // Add the digits from the end
        big_int._number_array[index] = digit;
    }

    return in;
}

bool BigInteger::operator==(int number) const {
    return _equals_integer(*this, number);
}

bool BigInteger::operator==(const BigInteger &big_int) const {
    return _equals(*this, big_int);
}

bool BigInteger::operator!=(int number) const {
    return !(*this == number);
}

bool BigInteger::operator!=(const BigInteger &big_int) const {
    return !(*this == big_int);
}

bool BigInteger::operator<(int number) const {
    return _less(*this, BigInteger(number));
}

bool BigInteger::operator<(const BigInteger &big_int) const {
    return _less(*this, big_int);
}

bool BigInteger::operator<=(int number) const {
    return (*this < BigInteger(number)) || (*this == number);
}

bool BigInteger::operator<=(const BigInteger &big_int) const {
    return (*this < big_int) || (*this == big_int);
}

bool BigInteger::operator>(int number) const {
    return !(*this < number) && (*this != number);
}

bool BigInteger::operator>(const BigInteger &big_int) const {
    return !(*this < big_int) && (*this != big_int);
}

bool BigInteger::operator>=(int number) const {
    return !(*this < number) || (*this == number);
}

bool BigInteger::operator>=(const BigInteger &big_int) const {
    return !(*this < big_int) || (*this == big_int);
}

BigInteger::operator int() const {
    // Maximum length for an int
    if (_length > 10)
        throw runtime_error("Cannot convert to int: Number is too large.");

    int sum = 0;
    int factor = 1;

    for (size_t i = 0; i < _length; ++i) {
        sum += _number_array[i] * factor;
        factor *= 10;
    }

    if (!_positive) {
        sum = -sum;
    }

    if (sum < INT_MIN || sum > INT_MAX) {
        throw runtime_error("Cannot convert to int: Result is out of int range.");
    }

    return sum;
}

BigInteger &BigInteger::operator+=(const BigInteger &big_int) {
    if (_positive == big_int._positive)
        return _add(*this, big_int);

    BigInteger temp_int(big_int);
    BigInteger temp_this(*this);
    temp_int._positive = true;
    temp_this._positive = true;

    if (temp_this < temp_int) {
        temp_this = _subtract(temp_int, temp_this);
        temp_this._positive = !_positive;
    }
    else
        _subtract(temp_this, temp_int);

    *this = temp_this;
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger &big_int) const {
    BigInteger temp(*this);
    temp += big_int;
    return temp;
}

BigInteger &BigInteger::operator-=(const BigInteger &big_int) {
    BigInteger temp(big_int);
    temp._positive = !temp._positive;
    return (*this += temp);
}

BigInteger BigInteger::operator-(const BigInteger &big_int) const {
    BigInteger temp(*this);
    temp -= big_int;
    return temp;
}

BigInteger &BigInteger::operator*=(const BigInteger &big_int) {
    if (big_int._is_zero())
        *this = big_int;
    else
        _multiply(*this, big_int);

    return *this;
}

BigInteger BigInteger::operator*(const BigInteger &big_int) const {
    BigInteger temp(*this);
    temp *= big_int;
    return temp;
}

BigInteger BigInteger::operator*(int number) const {
    BigInteger temp(*this);
    temp *= BigInteger(number);
    return temp;
}

BigInteger &BigInteger::operator/=(const BigInteger &big_int) {
    if (*this == 0 || big_int == 1)
        return *this;
    if (big_int._is_zero())
        throw runtime_error("Can't divide by 0!");
    if (_positive == big_int._positive && big_int > *this) {
        *this = BigInteger();
        return *this;
    }
    if (*this == big_int) {
        *this = BigInteger(1);
        return *this;
    }

    return _divide(*this, big_int);
}

BigInteger BigInteger::operator/(const BigInteger &big_int) const {
    BigInteger temp(*this);
    temp /= big_int;
    return temp;
}

BigInteger &BigInteger::operator%=(const BigInteger &big_int) {
    if (big_int._is_zero())
        return *this;
    if (*this == 0 || (_positive == big_int._positive && big_int > *this))
        throw runtime_error("Can't divide by 0!");
    if (big_int == 1 || *this == big_int) {
        *this = BigInteger();
        return *this;
    }

    return _mod(*this, big_int);
}

BigInteger BigInteger::operator%(const BigInteger &big_int) const {
    BigInteger temp(*this);
    temp %= big_int;
    return temp;
}

BigInteger &BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger before(*this);
    *this += 1;
    return before;
}

BigInteger &BigInteger::operator--() {
    *this -= 1;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger before(*this);
    *this -= 1;
    return before;
}

BigInteger &BigInteger::operator^=(int number) {
    if (number == 0) {
        *this = BigInteger(1);
        return *this;
    }

    BigInteger temp(*this);
    for (int i = 0; i < number - 1; i++) {
        *this *= temp;
    }

    return *this;
}

BigInteger BigInteger::operator^(int number) const {
    BigInteger temp(*this);
    temp ^= number;
    return temp;
}

/**
 *
 * ~Helper Methods~
 *
 */
bool BigInteger::_equals(const BigInteger &big_int_1, const BigInteger &big_int_2) {
    if (big_int_1._positive != big_int_2._positive || big_int_1._length != big_int_2._length) return false;

    for (size_t i = 0; i < big_int_1._length; i++)
        if (big_int_1._number_array[i] != big_int_2._number_array[i]) return false;

    return true;
}

bool BigInteger::_equals_integer(const BigInteger &big_int, int number) {
    if (number == 0 && big_int._is_zero())
        return true;

    if ((number >= 0 && !big_int._positive) || (number < 0 && big_int._positive))
        return false;

    size_t i = 0;
    number = abs(number);

    while (number > 0) {
        if (number % 10 != big_int._number_array[i])
            return false;

        number /= 10;
        i++;
    }

    return i == big_int._length - 1;
}

void BigInteger::_assign(const BigInteger &big_int) {
    _length = big_int._length;
    _positive = big_int._positive;

    for (size_t i = 0; i < _length; i++)
        _number_array[i] = big_int._number_array[i];
}

void BigInteger::_assign_integer(int number) {
    _positive = (number >= 0);

    number = abs(number);
    while (number > 0) {
        _number_array[_length] = number % 10;
        number /= 10;
        _length++;
    }
}

bool BigInteger::_abs_less(const BigInteger &big_int_1, const BigInteger &big_int_2) {
    if (big_int_1._length != big_int_2._length) return big_int_1._length < big_int_2._length;

    for (size_t i = 0; i < big_int_1._length; i++) {
        size_t index = big_int_1._length - 1 - i;
        int digit_1 = big_int_1._number_array[index];
        int digit_2 = big_int_2._number_array[index];

        if (digit_1 != digit_2) return digit_1 < digit_2;
    }

    return false;
}

bool BigInteger::_less(const BigInteger &big_int_1, const BigInteger &big_int_2) {
    // big_int_1 < big_int_2
    // - && +
    if (!big_int_1._positive && big_int_2._positive) return true;
    // + && -
    if (big_int_1._positive && !big_int_2._positive) return false;
    // + && +
    if (big_int_1._positive) return _abs_less(big_int_1, big_int_2);
    // - && -
    return !_abs_less(big_int_1, big_int_2);
}

bool BigInteger::_is_sign(char character) {
    return character == 45 || character == 43;
}

BigInteger &BigInteger::_add(BigInteger &big_int_1, const BigInteger &big_int_2) {
    size_t length = big_int_2._length;

    if (big_int_1._length < big_int_2._length) {
        for (size_t i = big_int_1._length; i < big_int_2._length; i++)
            big_int_1._number_array[i] = 0;

        big_int_1._length = big_int_2._length;
    }

    int cargo = 0;
    for (size_t i = 0; i < length; i++) {
        int sum = big_int_1._number_array[i] + big_int_2._number_array[i] + cargo;
        cargo = 0;
        big_int_1._number_array[i] = sum % 10;

        if (sum / 10 != 0)
            cargo++;
    }

    if (cargo > 0) {
        if (big_int_1._length == MAX) throw runtime_error("Number overflow!");
        big_int_1._number_array[length] = cargo;
        big_int_1._length++;
    }

    return big_int_1;
}

BigInteger &BigInteger::_subtract(BigInteger &big_int_1, const BigInteger &big_int_2) {
    if (big_int_1 < big_int_2) {
        throw runtime_error(
                "Subtraction would result in a negative number, which is not supported in this implementation.");
    }

    int borrow = 0;
    for (size_t i = 0; i < big_int_1._length; ++i) {
        int diff = big_int_1._number_array[i] - (i < big_int_2._length ? big_int_2._number_array[i] : 0) - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        big_int_1._number_array[i] = diff;
    }

    // Remove leading zeros
    while (big_int_1._length > 1 && big_int_1._number_array[big_int_1._length - 1] == 0) {
        --big_int_1._length;
    }

    return big_int_1;
}

BigInteger &BigInteger::_multiply(BigInteger &big_int_1, const BigInteger &big_int_2) {
    BigInteger result;
    size_t length_1 = big_int_1._length;
    size_t length_2 = big_int_2._length;

    // Result can be at most length_1 + length_2 digits
    result._length = length_1 + length_2;
    if (result._length > MAX)
        throw runtime_error("Result of the multiplication is too big");

    result._positive = (big_int_1._positive == big_int_2._positive);

    // Initialize result number array to zero
    for (size_t i = 0; i < result._length; i++) {
        result._number_array[i] = 0;
    }

    // Multiply each digit of big_int_1 with each digit of big_int_2
    for (size_t i = 0; i < length_1; i++) {
        int carry = 0;
        for (size_t j = 0; j < length_2; j++) {
            int product = big_int_1._number_array[i] * big_int_2._number_array[j] + result._number_array[i + j] + carry;
            carry = product / 10;
            result._number_array[i + j] = product % 10;
        }
        // Add remaining carry
        result._number_array[i + length_2] += carry;
    }

    // Remove leading zeros from the result
    while (result._length > 1 && result._number_array[result._length - 1] == 0) {
        result._length--;
    }

    big_int_1 = result;
    return big_int_1;
}

BigInteger &BigInteger::_divide(BigInteger &big_int_1, const BigInteger &big_int_2) {
    int i, res_length = 0, cc;
    int res[big_int_1._length];
    BigInteger temp;

    for (i = (int) big_int_1._length - 1; (temp * 10) + (BigInteger) big_int_1._number_array[i] < big_int_2; i--) {
        temp *= 10;
        temp += big_int_1._number_array[i];
    }

    for (; i >= 0; i--) {
        temp = (temp * 10) + (BigInteger) big_int_1._number_array[i];

        for (cc = 9; big_int_2 * cc > temp; cc--);
        temp -= big_int_2 * cc;
        res[res_length++] = cc;
    }

    big_int_1._length = sizeof(res) / sizeof(res[0]);

    for (i = 0; i < res_length; i++)
        big_int_1._number_array[i] = res[res_length - i - 1];
    big_int_1._length = res_length;

    return big_int_1;
}

BigInteger &BigInteger::_mod(BigInteger &big_int_1, const BigInteger &big_int_2) {
    int i, res_length = 0, cc;
    int res[big_int_1._length];
    BigInteger temp;

    for (i = (int) big_int_1._length - 1; (temp * 10) + (BigInteger) big_int_1._number_array[i] < big_int_2; i--) {
        temp *= 10;
        temp += big_int_1._number_array[i];
    }
    for (; i >= 0; i--) {
        temp = (temp * 10) + (BigInteger) big_int_1._number_array[i];

        for (cc = 9; big_int_2 * cc > temp; cc--);
        temp -= big_int_2 * cc;
        res[res_length++] = cc;
    }

    big_int_1 = temp;
    return big_int_1;
}

bool BigInteger::_is_zero() const {
    return _length == 1 && _number_array[0] == 0;
}
