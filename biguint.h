#ifndef BIGUINT_H
#define BIGUINT_H

#include <cstdlib>
#include <string>

class biguint
{
public:
    // TYPES and CONSTANTS
    typedef std::size_t size_type;
    typedef unsigned int digit_type; // digits must be a nonnegative int
    static const size_type CAPACITY = 10;

// CONSTRUCTORS

    // pre: none
    // post: creates a biguint with given unsigned integer value (default value = 0)
    biguint(std::size_t = 0); // it's ok that there's no variable name here since you won't refer to it in the constructor, it just sets the initial value

    // pre: s.size() <= CAPACITY && s consists of decimal digits only
    // post: creates a biguint whose digits are given in a string s
    //       rightmost digit of s corresponds to the least significant digit
    biguint (const std::string & s);

    // pre: none
    // post: creates a biguint with the same value as b // copying it
    biguint(const biguint & b); // use the value but don't change b

// CONSTANT FUNCTIONS
    // pre: pos < CAPACITY
    // post: returns the (pos+1)^st digit from the right of this biguint
    digit_type operator [](size_type pos) const;

    // pre: none
    // post: returns the number of digits in this biguint (not counting leading zeros)
    size_type size() const;

    // pre: none
    // post: return 0 if this biguint == n
    //             -1 if this biguint < n
    //              1 if this biguint > n
    int compare(const biguint & n) const;


    // MODIFICATION FUNCTIONS
    // SHIFT member functions

    // pre: none
    // post: digits of this biguint has been left shifted by n positions
    //       the former n most significant digits are discarded
    //       the new n least significiant digits are 0
    void ls (size_type n);

    // pre: none
    // post: digits of this biguint has been right shifted by n positions
    //       the former n least significant digits are discarded
    //       the new n most significant digit are 0
    void rs (size_type n);


    // ARITHMETIC member operators

    // pre: none
    // post: b has been added to this biguint
    //       overflow digit will be thrown away, if any
    void operator +=(const biguint &b);

    // pre: none
    // post: if b > this biguint, then this biguint is reset to 0
    //       else b is subtracted from this biguint
    void operator -=(const biguint & b);

    // pre: d represents a decimal digit
    // post: this biguint has been multiplied by d; overflow digit is discarded
    void operator *= (digit_type d);

    // pre: none
    // post: this biguint has been multiplied by b; overflow digits are discarded
    void operator *= (const biguint & b);

    // pre: b != 0
    // post: this biguint has been divided by b; the result is rounded down to the nearest integer
    void operator /= (const biguint & b);

    // pre: b != 0
    // post: this biguint has been modded by b;
    //       the new value is the remainder when dividing the original value by b
    void operator %= (const biguint & b);

    // pre: none
    // post: this biguint has been incremented/decremented by 1
    //       return value is the new value (pre)
    biguint operator++();
    biguint operator--();

    // pre: none
    // post: this biguint has been incremented/decremented by 1
    //       return value is the original value (post)
    biguint operator++(int);
    biguint operator--(int);

private:
    digit_type _data[CAPACITY];

    // _data[i] corresponds to the (i+1)^st rightmost digit of this biguint (0 if it is not used)
    // _data[0] = least significant (units) digit
    // _data[CAPACITY-1] = most significant digit
};

// NON-MEMBER OPERATORS

// I/O operators
std::ostream & operator <<(std::ostream & os, const biguint &);
std::istream & operator >>(std::istream & is, biguint &);

// ARITHMETIC operators
biguint operator + (const biguint &, const biguint &);
biguint operator - (const biguint &, const biguint &);
biguint operator * (const biguint &, const biguint &);
biguint operator / (const biguint &, const biguint &);
biguint operator % (const biguint &, const biguint &);

// COMPARISON operators
bool operator <(const biguint &, const biguint &);
bool operator <=(const biguint &, const biguint &);
bool operator ==(const biguint &, const biguint &);
bool operator !=(const biguint &, const biguint &);
bool operator >=(const biguint &, const biguint &);
bool operator >(const biguint &, const biguint &);

// SHIFT operators
biguint operator << (const biguint &, unsigned int);
biguint operator >> (const biguint &, unsigned int);
#endif // BIGUINT_H




/*
vector<biguint::size_type> create_array(biguint::size_type num) {
    biguint::size_type current_digit;
    vector<biguint::size_type> fake_array;
    vector<biguint::size_type> new_array;

    while (num >= 1) {
        current_digit = num % 10;
        fake_array.push_back(current_digit);
        num /= 10;
    }

    for (int i=0; i<fake_array.size(); ++i) {
        new_array.push_back(fake_array[i]);
    }

    for (int i=fake_array.size(); i<biguint::CAPACITY; ++i) {
        new_array.push_back(0);
    }

    return new_array;
}
*/
