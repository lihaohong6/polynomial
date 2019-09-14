#include <iostream>
#include "big_integer.h"
#include "polynomial.h"

using namespace std;

const int SAMPLE_SIZE = 230;

int main() {

    vector<big_integer> v[19];
    int nums[] = {0, 40, 40, 40, 40, 40, 40, 47, 48, 50, 50, 51, 52, 56, 60, 60, 67, 75, 91};
    for (int i = 1; i <= 18; i++) {
        v[i].emplace_back(nums[i]);
        v[i].emplace_back(SAMPLE_SIZE - nums[i]);
    }

    polynomial pols[19];
    for (int i = 1; i <= 18; i++) {
        pols[i] = polynomial(&v[i]);
    }
    polynomial product = polynomial(pols[1]);
    for (int i = 2; i <= 18; i++) {
        product = product * pols[i];
    }
    cout<<product<<endl;

    big_integer bi(230), ans(1);
    for (int i = 1; i <= 17; i++)
        ans = ans * bi;
    cout<<ans<<endl;

    return 0;
}
