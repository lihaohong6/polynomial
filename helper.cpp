//
// Created by Haohong Li on 2/21/18.
//

#include "helper.h"
#include "big_integer.h"


template<class T>
inline void helper::expand_vector(std::vector<T> *a, long length) {
    T val(0);
    if (a->size() < length)
        for (; a->size() != length; a->push_back(val));
}

template<class T>
inline void helper::remove_zero(std::vector<T> *a) {
    T zero(0);
    for (; !a->empty() && (a->back() == zero); a->pop_back());
}

template<class T>
inline std::vector<T> helper::reverse_vector(std::vector<T> *a) {
    vector<T> reversed(a->size());
    for (int i = 0; i < a->size(); i++) {
        reversed[i] = (*a)[a->size() - i - 1];
    }
    return reversed;
}


template void helper::expand_vector<int>(std::vector<int> *a, long length);
template void helper::expand_vector<big_integer>(std::vector<big_integer> *a, long length);

template void helper::remove_zero<int>(std::vector<int> *a);
template void helper::remove_zero<big_integer>(std::vector<big_integer> *a);

template vector<big_integer> helper::reverse_vector<big_integer>(std::vector<big_integer> *a);