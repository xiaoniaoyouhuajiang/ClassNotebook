#ifndef VECTOR__H
#define VECTOR__H

#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

#include "vector.h"

namespace stepik {

template <typename Type>
class vector_dek : public vector<Type> {
public:

    explicit vector_dek(size_t count = 0): vector<Type>(count) {}

    void Dekart(const vector<Type> &vector1, const vector<Type> &vector2) {
        for(size_t i = 0, s = this->size(); i < s; i++) {
            this->at(i) = vector1[i] * vector2[i];
        }
    }
};
}
#endif // VECTOR__H
