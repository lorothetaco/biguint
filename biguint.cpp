#include "biguint.h"
#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
#include <vector>
#include <cmath>

using namespace std;

bool digits_only(const string & str) {
    for (int i=0; i<str.length(); ++i) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

// CONSTRUCTORS
biguint::biguint(size_type szt) {

    // first setting all to zero
    for (int i=0; i<CAPACITY; ++i)
        _data[i] = 0;

    // counting number of digits in it
    int count_digits = 0;
    int temp_num = szt;
    while (temp_num >= 1) {
        temp_num /= 10;
        count_digits ++;
    }

    // replacing stuff in data with modulo of szt
    for (int i=0; i<count_digits; ++i) {
        _data[i] = szt%10;
        szt /= 10;
    }
}

biguint::biguint(const string & s) {
    assert(s.size()<= CAPACITY && digits_only(s));
    biguint::size_type szt = stoull(s);

    for (int i=0; i<CAPACITY; ++i)
        _data[i] = 0;

    int count_digits = 0;
    int temp_num = szt;
    while (temp_num >= 1) {
        temp_num /= 10;
        count_digits ++;
    }

    for (int i=0; i<count_digits; ++i) {
        _data[i] = szt%10;
        szt /= 10;
    }
}

biguint::biguint(const biguint & b) {
    for (int i=0; i<CAPACITY; ++i)
        _data[i] = b._data[i];
}


// CONSTANT FUNCTIONS

biguint::digit_type biguint::operator [](size_type pos) const { // allows you to access elements of a biguint object using array-like syntax.
    assert(pos < CAPACITY);
    return _data[pos];
}

biguint::size_type biguint::size() const {
    for (int i=CAPACITY-1; i>0; --i) {
        if (_data[i] != 0) {
            return i + 1;
        }
    }
    return 1;
}

int biguint::compare(const biguint & n) const {
    for (int i=CAPACITY-1; i>=0; --i) {
        if (_data[i]>n[i])
            return 1;
        else if (_data[i]<n[i])
            return -1;
    }
    return 0;
}

// MODIFICATION FUNCTIONS

// shift member functions
void biguint::ls(size_type n) {
    // get the size of the current biguint
    int start = size();

    for (int i=start; i>=0; --i) {
        if (i+n < CAPACITY) {
            _data[i+n] = _data[i];
        }
        _data[i] = 0;
    }
}


void biguint::rs(size_type n) {
    for (int i=0; i<CAPACITY; ++i) {
        if (i<CAPACITY-n)
            _data[i] = _data[i+n];
        else
            _data[i] = 0;
    }
}

// arithmetic member operators
void biguint::operator += (const biguint & b) {
    for (int i=0; i<CAPACITY; ++i) {
        _data[i] += b[i];
        if (_data[i] > 9) {
            _data[i] -= 10;
            if (i+1<CAPACITY)
                _data[i+1]++;
        }
    }
}

void biguint::operator -= (const biguint & b) {
    if (b > *this) {
        for (int i=0; i<CAPACITY; ++i) {
            _data[i] = 0;
        }
    }
    else {
        for (int i=0; i<CAPACITY-1; ++i) {
            if (_data[i] >= b[i])
                _data[i] -= b[i];
            else {
                _data[i] += 10;
                _data[i+1] --;
                _data[i] -= b[i];
            }
        }
        _data[CAPACITY-1] -= b[CAPACITY-1];
    }
}

void biguint::operator *= (digit_type d) {
    int temp_tens = 0;
    for (int i=0; i<CAPACITY; ++i) {
        _data[i] *= d;
        if (_data[i] > 9) {
            temp_tens = _data[i] / 10;
            _data[i] %= 10;
            if (i+1<CAPACITY)
                _data[i+1] += temp_tens;
        }
    }
}


void biguint::operator *= (const biguint & b) {
    biguint sum(0);
    int product = 0;
    int carryover = 0;

    // i + j helps keep track of which place value we're at; 1+1 (10^1 * 10^1) means we're in hundreds, same as 2+0
    for (int i=0; i<CAPACITY; ++i) {
        carryover = 0;
        for (int j=0; j<CAPACITY; ++j) {
            if (i + j < CAPACITY) {
                product = _data[i] * b[j] + sum[i+j] + carryover;
                sum._data[i+j] = product % 10;
                carryover = product / 10;
            }
        }
    }

    for (int i=0; i<CAPACITY; ++i) {
        _data[i] = sum._data[i];
    }
}

biguint biguint::operator++() {
    *this += 1;
    return *this;
}

biguint biguint::operator--() {
    *this -= 1;
    return *this;
}

biguint biguint::operator++(int a) {
    biguint b(*this);
    *this += 1;
    return b;
}

biguint biguint::operator--(int a) {
    biguint b(*this);
    *this -= 1;
    return b;
}

// non-member operators
// I/O operators

ostream & operator << (ostream & os, const biguint & bgut) {
    for (int i = bgut.size()-1; i>=0; --i) {
        os << bgut[i];
    }

    //os << endl;
    return os;
}

istream & operator >> (istream & is, biguint & bgt) {
    string temp;
    is >> temp;
    bgt = biguint(temp);
    return is;
}

// ARITHMETIC operators

biguint operator + (const biguint & a, const biguint & b) {
    biguint c = a;
    c += b;
    return c;
}

biguint operator - (const biguint & a, const biguint & b) {
    biguint c = a;
    c -= b;
    return c;
}

biguint operator * (const biguint & a, const biguint & b) {
    biguint c = a;
    c *= b;
    return c;
}

// COMPARISON operators
bool operator < (const biguint & a, const biguint & b) {
    if (a.compare(b) == -1)
        return true;
    else
        return false;
}
bool operator <=(const biguint & a, const biguint & b) {
    if (a.compare(b) == -1 || a.compare(b) == 0)
        return true;
    else
        return false;
}
bool operator ==(const biguint & a, const biguint & b) {
    if (a.compare(b) == 0)
        return true;
    else
        return false;
}
bool operator !=(const biguint & a, const biguint & b) {
    if (a.compare(b) == 0)
        return false;
    else
        return true;
}
bool operator >=(const biguint & a, const biguint & b) {
    if (a.compare(b) == -1)
        return false;
    else
        return true;
}
bool operator >(const biguint & a, const biguint & b) {
    if (a.compare(b) == 1)
        return true;
    else
        return false;
}

// SHIFT operators
biguint operator << (const biguint & bgut, unsigned int num) {
    biguint new_bgut(bgut);
    new_bgut.ls(num);
    return new_bgut;
}

biguint operator >> (const biguint & bgut, unsigned int num) {
    biguint new_bgut(bgut);
    new_bgut.rs(num);
    return new_bgut;
}

/*
 * void biguint::ls(size_type n) {
 * int start_size = size();
 *
 * for (int i=start.size - 1; i>= 0; --i) {
 * if (i+n >= start_size)
 * continue;
 *
 * _data[i+n] = _data[i];
 *
 * if (i<=n) {
 * _data[i] = 0;
 * }
 */

/*
void biguint::ls(size_type n) {
    int start_size = size();
    for (int i=start.size -1; i>=0; --i) {
        if(i+n >= start_size)
            continue;
        _data[i+n] = _data[i];
        if (i<= n) {
            _data[i] = 0;
        }
    }
}
*/
