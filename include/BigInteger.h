#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include <string>

#define MAX 100000

class BigInteger {
    int _number_array[MAX]{};
    bool _positive{};
    size_t _length = 0;
public:
    /**      ~Constructors~      **/
    BigInteger();

    BigInteger(int number);

    BigInteger(std::string number);

    BigInteger(const int *number_array, size_t length, bool positive);

    BigInteger(const BigInteger &big_int);

    ~BigInteger();

    /**      ~Operators~      **/
    BigInteger &operator=(int number);

    BigInteger &operator=(const BigInteger &big_int);

    bool operator==(int number) const;

    bool operator==(const BigInteger &big_int) const;

    bool operator!=(int number) const;

    bool operator!=(const BigInteger &big_int) const;

    bool operator<(int number) const;

    bool operator<(const BigInteger &big_int) const;

    bool operator<=(int number) const;

    bool operator<=(const BigInteger &big_int) const;

    bool operator>(int number) const;

    bool operator>(const BigInteger &big_int) const;

    bool operator>=(int number) const;

    bool operator>=(const BigInteger &big_int) const;

    operator int() const;

    BigInteger &operator+=(const BigInteger &big_int);

    BigInteger operator+(const BigInteger &big_int) const;

    BigInteger &operator-=(const BigInteger &big_int);

    BigInteger operator-(const BigInteger &big_int) const;

    BigInteger &operator*=(const BigInteger &big_int);

    BigInteger operator*(const BigInteger &big_int) const;

    BigInteger operator*(int number) const;

    BigInteger &operator/=(const BigInteger &big_int);

    BigInteger operator/(const BigInteger &big_int) const;

    BigInteger &operator%=(const BigInteger &big_int);

    BigInteger operator%(const BigInteger &big_int) const;

    BigInteger &operator++();

    BigInteger operator++(int);

    BigInteger &operator--();

    BigInteger operator--(int);

    BigInteger &operator^=(int number);

    BigInteger operator^(int number) const;

    friend std::ostream &operator<<(std::ostream &out, const BigInteger &big_int);

    friend std::istream &operator>>(std::istream &in, BigInteger &big_int);

private:
    /**      ~Helper Methods~      **/
    void _assign(const BigInteger &big_int);

    void _assign_integer(int number);

    bool _is_zero() const;

    static void _assign_string(std::string &input, BigInteger &big_int);

    static BigInteger &_add(BigInteger &big_int_1, const BigInteger &big_int_2);

    static BigInteger &_subtract(BigInteger &big_int_1, const BigInteger &big_int_2);

    static BigInteger &_multiply(BigInteger &big_int_1, const BigInteger &big_int_2);

    static BigInteger &_divide(BigInteger &big_int_1, const BigInteger &big_int_2);

    static BigInteger &_mod(BigInteger &big_int_1, const BigInteger &big_int_2);

    static bool _less(const BigInteger &big_int_1, const BigInteger &big_int_2);

    static bool _abs_less(const BigInteger &big_int_1, const BigInteger &big_int_2);

    static bool _equals(const BigInteger &big_int_1, const BigInteger &big_int_2);

    static bool _equals_integer(const BigInteger &big_int, int number);

    static bool _is_sign(char character);
};

#endif //BIGINTEGER_BIGINTEGER_H
