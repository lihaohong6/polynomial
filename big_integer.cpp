/**
 * @author Peter (Haohong) Li
 * A big_integer class that
 */
// referenced the java BigInteger class

#include "big_integer.h"
#include <vector>
#include <cmath>
#include "helper.h"

// using namespace std;

big_integer::big_integer() : big_integer((long long)0){}

big_integer::big_integer(short x) : big_integer((long long) x) {}

big_integer::big_integer(int x) : big_integer((long long) x) {}

big_integer::big_integer(long x) : big_integer((long long) x) {}

big_integer::big_integer(long long x) {
    if (x > 0)
        sig_num = 1;
    else if (x < 0) {
        sig_num = -1;
        x = -x;
    } else {
        sig_num = 0;
        mag.push_back(0);
        digits = 1;
        return;
    }

    for (; x != 0;) {
        mag.push_back((int) (x % 10));
        x /= 10;
    }
    digits = mag.size();
}

big_integer::big_integer(vector<int> a, int sig_num) {
    this->mag = a;
    this->digits = a.size();
    this->sig_num = sig_num;
}

char *big_integer::to_string() const {
    char *ans, *p;
    if (sig_num == -1) {
        ans = new char[digits + 2];
        *ans = '-';
        p = ans + 1;
    } else if (sig_num == 1) {
        ans = new char[digits + 1];
        p = ans;
    } else {
        ans = new char[2];
        ans[0] = '0';
        ans[1] = '\0';
        return ans;
    }
    for (int i = digits - 1; i >= 0; i--, p++) {
        *p = (char) (mag[i] + 48);
    }
    *p = '\0';

    return ans;
}

int big_integer::compare_mag(big_integer o) const {
    if (this->mag.size() > o.mag.size())
        return 1;
    if (this->mag.size() < o.mag.size())
        return -1;

    for (int i = (int) o.mag.size() - 1; i >= 0; i--) {
        if (o.mag[i] != this->mag[i])
            return (int) (this->mag[i] > o.mag[i]) * 2 - 1;
    }
    return 0;
}

vector<int> big_integer::sum(big_integer *a, big_integer *b) const {
    vector<int> ans;
    vector<int> vector1 = a->mag;
    vector<int> vector2 = b->mag;
    int length = (int) max(vector1.size(), vector2.size());

    helper::expand_vector<int>(&vector1, length);
    helper::expand_vector<int>(&vector2, length);

    int sum, next_digit = 0;
    for (int i = 0; i < length; i++) {
        sum = vector1[i] + vector2[i] + next_digit;
        next_digit = sum / 10;
        ans.push_back(sum % 10);
    }
    if (next_digit == 1)
        ans.push_back(1);
    return ans;
}

vector<int> big_integer::difference(big_integer *x, big_integer *y) const {
    vector<int> ans;
    vector<int> a = x->mag;
    vector<int> b = y->mag;

    int length = (int) max(a.size(), b.size());

    helper::expand_vector<int>(&a, length);
    helper::expand_vector<int>(&b, length);

    int difference, next_digit = 0;
    for (int i = 0; i < length; i++) {
        difference = a[i] - b[i] + next_digit;
        next_digit = (difference + 10) / 10 - 1;
        ans.push_back((difference + 10) % 10);
    }
    // next_digit may possibly be -1, but that will be ignored
    helper::remove_zero<int>(&ans);
    return ans;
}

bool big_integer::operator!=(big_integer o) const {
    return !(*this == o);
}

bool big_integer::operator==(big_integer o) const {
    if (this->mag.size() != o.mag.size())
        return false;
    if (this->sig_num != o.sig_num)
        return false;

    return this->compare_mag(o) == 0;
}

bool big_integer::operator<(big_integer o) const {
    if (this->sig_num < o.sig_num)
        return true;
    if (this->sig_num > o.sig_num)
        return false;
    if (this->sig_num == 0)
        return false;

    return this->sig_num == 1 == (this->compare_mag(o) == -1);
}

bool big_integer::operator>(big_integer o) const {
    return !(*this == o || *this < o);
}

bool big_integer::operator<=(big_integer o) const {
    return !(*this > o);
}

bool big_integer::operator>=(big_integer o) const {
    return !(*this < o);
}

big_integer big_integer::operator+(big_integer o) const {
    big_integer self(*this);
    if (sig_num == o.sig_num) {
        if (sig_num == -1)
            return big_integer(sum(&self, &o), -1);
        if (sig_num == 1)
            return big_integer(sum(&self, &o), 1);
        return big_integer(0);
    }

    int comp = this->compare_mag(o);
    if (comp == 0)
        return big_integer(0);
    if (comp == 1)
        return big_integer(difference(&self, &o), this->sig_num);
    return big_integer(difference(&o, &self), o.sig_num);
}

big_integer big_integer::operator-(big_integer o) const {
    big_integer new_o(o.mag, 0 - o.sig_num);
    big_integer ans = *this + new_o;
    return ans;
}
big_integer big_integer::operator-(long long o) const {
    return *this - big_integer(o);
}

big_integer big_integer::operator*(big_integer o) const {
    int result_sign = this->sig_num * o.sig_num;
    if (result_sign == 0)
        return big_integer(0);

    vector<int> ans(this->mag.size() + o.mag.size());

    for (int i = 0; i < this->mag.size(); i++) {
        for (int j = 0; j < o.mag.size(); j++) {
            ans[i + j] += this->mag[i] * o.mag[j];
            ans[i + j + 1] += ans[i + j] / 10;
            ans[i + j] %= 10;
        }
    }

    helper::remove_zero<int>(&ans);
    return big_integer(ans, result_sign);
}

big_integer big_integer::operator/(big_integer o) {
    // not implemented because
}

big_integer big_integer::operator+=(big_integer o) {
    *this = *this + o;
    return *this;
}

big_integer big_integer::factorial() const {
    big_integer ans(1);
    big_integer num(this->mag, 1);
    big_integer zero(0);
    while(num != zero) {
        ans = ans * num;
        num = num - 1;
    }
    return ans;
}

big_integer big_integer::pow(long x) const {
    big_integer ans(*this);
    for (long i = 2; i <= x; i++) {
        ans = ans * (*this);
    }
    return ans;
}

char big_integer::operator[](int x) {
    return (char)(mag[mag.size() - x - 1] + 48);
}

ostream &operator<<(ostream &os, const big_integer &number) {
    os << number.to_string();
    return os;
}