#ifndef ALG_HPP
#define ALG_HPP

#include "point.h"
#include "shape.hpp"
#include "vector.hpp"
#include "shared_ptr.hpp"

typedef stepik::shared_ptr<Shape> vect_elem_type;
typedef stepik::vector<vect_elem_type> vect_type;
typedef size_t index_type;

index_type getMaxSq(const vect_type & vect){
    index_type N = vect.size();
    index_type max = N;
    double sq = 0;
    for (index_type i = 0; i < N; i++){
        if (vect[i]->square() > sq){
            sq = vect[i]->square();
            max = i;
        }
    }
    return max;
}

void replaceSq(vect_type & vect, const vect_elem_type & el, double sq){
   index_type N = vect.size();
   for (index_type i = 0; i < N; i++){
        if (vect[i]->square() > sq){
            vect[i] = el;
        }
    }
}

void printMaxSq(vect_type & vect){
    index_type N = vect.size();
    index_type max = N;
    double sq = 0;
    for (index_type i = 0; i < N; i++){
        if (vect[i]->square() > sq){
            sq = vect[i]->square();
            max = i;
            cout << sq << endl;
        }
    }
}

#endif