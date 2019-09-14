//
// Created by Haohong Li on 2/20/18.
//

#ifndef POLYNOMIAL_POLYNOMIAL_H
#define POLYNOMIAL_POLYNOMIAL_H

#include<vector>
#include "big_integer.h"

using namespace std;

class polynomial {

private:
    vector<big_integer> mag;

public:
    /**
     * constructs a polynomial f(x) = 0
     */
    polynomial();

    /**
     * construct a polynomial object given the coefficients of each
     * power stored as ints
     * @param x is a vector that stores coefficients using the natural
     * ordering of a polynomial (highest power first)
     */
    explicit polynomial(vector<int> x);

    /**
     * constructs a polynomial object given the coefficients of each
     * power stored as big_integer
     * @param x is a vector that stores coefficients using the reverse
     * of the natural order of a polynomial (lowest power first)
     */
    explicit polynomial(vector<big_integer> *x);

    std::string to_string() const;

    polynomial operator=(polynomial o);

    polynomial operator+(polynomial o) const;

    polynomial operator-(polynomial o);

    polynomial operator*(polynomial o) const;

    polynomial operator/(big_integer o);

    polynomial operator/(polynomial o);

    polynomial pow(long x) const;

    polynomial derivative() const;

    friend ostream &operator<<(ostream &os, const polynomial &pol);
};


#endif //POLYNOMIAL_POLYNOMIAL_H
