//
// Created by Haohong Li on 2/20/18.
//

#include "polynomial.h"
#include "helper.h"
#include <vector>

using namespace std;

polynomial::polynomial() {
    this->mag.emplace_back(big_integer(0));
}

polynomial::polynomial(vector<int> x) {
    for (auto i = (int) (x.size() - 1); i >= 0; i--) {
        mag.emplace_back(big_integer(x[i]));
    }
}

/**
 * creates a polynomial based on a vector that provides the coefficients
 * @param x is the vector representing the coefficients of the polynomial
 * using the natural ordering of a polynomial (highest power first)
 */
polynomial::polynomial(vector<big_integer> *x) {
    /* pass the address because otherwise the parameter
     * will be copied twice */
    mag = helper::reverse_vector<big_integer>(x);
    helper::remove_zero(&mag);
}

std::string polynomial::to_string() const {
    std::string ans;

    // the largest power
    long pow = mag.size() - 1;
    std::string coefficient(mag[pow].to_string());
    // treat the first one separately because it does not need a '+' sign
    ans = coefficient + "x^" + std::to_string(pow);

    for (long i = pow - 1; i >= 0; i--) {
        coefficient = mag[i].to_string();
        if (coefficient[0] != '0') {
            if (coefficient[0] != '-')
                ans += '+';
            ans += coefficient + "x^" + std::to_string(i);
        }
    }
    return ans;
}

polynomial polynomial::operator=(polynomial o) {
    (*this).mag = o.mag;
    return *this;
}

polynomial polynomial::operator+(polynomial o) const {
    unsigned long length = max(this->mag.size(), o.mag.size());
    vector<big_integer> ans(length);

    polynomial self = *this;
    helper::expand_vector<big_integer>(&(self.mag), length);
    helper::expand_vector<big_integer>(&(o.mag), length);

    for (unsigned long i = 0; i < length; i++) {
        ans[i] = this->mag[i] + o.mag[i];
    }
    helper::remove_zero(&ans);
    /* have to reverse the vector so that is uses the natural ordering
     * of a polynomial (highest power first) */
    ans = helper::reverse_vector<big_integer>(&ans);
    return polynomial(&ans);
}

polynomial polynomial::operator*(polynomial o) const {
    vector<big_integer> ans(this->mag.size() + o.mag.size() - 1);

    for (long i = 0; i < this->mag.size(); i++) {
        for (long j = 0; j < o.mag.size(); j++) {
            ans[i + j] += this->mag[i] * o.mag[j];
        }
    }
    helper::remove_zero(&ans);
    ans = helper::reverse_vector<big_integer>(&ans);
    return polynomial(&ans);
}

polynomial polynomial::pow(long x) const {
    polynomial ans = *this;
    for (int i = 2; i <= x; i++) {
        ans = ans * (*this);
    }
    return ans;
}

polynomial polynomial::derivative() const {
    vector<big_integer> ans(this->mag.size() - 1);
    for (long i = 0; i < ans.size(); i++) {
        ans[i] = this->mag[i + 1] * big_integer(i + 1);
    }
    ans = helper::reverse_vector(&ans);
    return *new polynomial(&ans);
}

ostream &operator<<(ostream &os, const polynomial &pol) {
    os << pol.to_string();
    return os;
}