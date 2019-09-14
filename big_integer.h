/**
 * @author Peter (Haohong) Li
 *
 */
#ifndef POLYNOMIAL_BIG_INTEGER_H
#define POLYNOMIAL_BIG_INTEGER_H

#include <iostream>
#include <vector>

using namespace std;

class big_integer {

private:
    int sig_num;
    vector<int> mag;
    int digits;

public:

    explicit big_integer();
    explicit big_integer(short x);
    explicit big_integer(int x);
    explicit big_integer(long x);
    explicit big_integer(long long x);
    explicit big_integer(vector<int> a, int sig_num);

    char* to_string() const;

private:
    int compare_mag(big_integer o) const;
    vector<int> sum(big_integer *a, big_integer *b) const;
    vector<int> difference(big_integer *a, big_integer *b) const;

public:

    bool operator!=(big_integer o) const;
    bool operator==(big_integer o) const;
    bool operator>(big_integer o) const;
    bool operator<(big_integer o) const;
    bool operator>=(big_integer o) const;
    bool operator<=(big_integer o) const;

    big_integer operator+(big_integer o) const;
    big_integer operator-(big_integer o) const;
    big_integer operator-(long long o) const;
    big_integer operator*(big_integer o) const;
    big_integer operator/(big_integer o);
    big_integer operator+=(big_integer o);

    big_integer factorial() const;
    big_integer pow(long x) const;

    char operator[](int x);

    friend ostream &operator<<(ostream &os, const big_integer &number);

};


#endif //POLYNOMIAL_BIG_INTEGER_H
