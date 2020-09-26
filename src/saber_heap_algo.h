#ifndef __SABERSTL_HEAP_ALHO_H__
#define __SABERSTL_HEAP_ALHO_H__

#include "saber_iterator.h"

namespace saberstl {

/* ----------- set_symmetric_difference ----------- */
/*
 * The function pass two iters, represent the begin and end of a heap container.
 * The new element is inserted into the end of heap
*/
template<class RandomIter, class Distance, class T>
void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIndex, T value) {
    auto parent = (holeIndex - 1) / 2;
    while (holeIndex > topIndex && *(first + parent) < value) {
        // Because using the operator '<', it is a max-heap
        *(first + holeIndex) = *(first + parent);
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    *(first + holeIndex) = value;
}

template<class RandomIter, class Distance>
void push_heap_d(RandomIter first, RandomIter last, Distance*) {
    saberstl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1));
}

template<class RandomIter>
void push_heap(RandomIter first, RandomIter last) {
    // The new element should be the end of the heap
    saberstl::push_heap_d(first, last, distance_type(first));
}

// Overloaded version
template<class RandomIter, class Distance, class T, class Compared>
void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIndex, T value, Compared comp) {
    auto parent = (holeIndex - 1) / 2;
    while (holeIndex > topIndex && comp(*(first + parent), value)) {
        *(first + holeIndex) = *(first + parent);
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    *(first + holeIndex) = value;
}

template<class RandomIter, class Distance, class Compared>
void push_heap_d(RandomIter first, RandomIter last, Distance*, Compared comp) {
    saberstl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1), comp);
}

template<class RandomIter, class Compared>
void push_heap(RandomIter first, RandomIter last, Compared comp) {
    saberstl::push_heap_d(first, last, distance_type(first), comp);
}


} // namespace saberstl


#endif // !__SABERSTL_HEAP_ALHO_H__