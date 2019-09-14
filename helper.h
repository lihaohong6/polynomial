//
// Created by Haohong Li on 2/21/18.
//

#ifndef POLYNOMIAL_HELPER_H
#define POLYNOMIAL_HELPER_H

#include <vector>

class helper {
public:
    template<class T>
    static void expand_vector(std::vector<T> *a, long length);

    template<class T>
    static void remove_zero(std::vector<T> *a);

    template<class T>
    static std::vector<T> reverse_vector(std::vector<T> *a);
};


#endif //POLYNOMIAL_HELPER_H
