#ifndef __SABERSTL_HEAP_ALHO_H__
#define __SABERSTL_HEAP_ALHO_H__

#include "saber_iterator.h"

namespace saberstl {

/* ----------- push_heap ----------- */
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


/* ----------- pop_heap ----------- */
/*
 * The function pass two iters, represent the begin and end of a heap container.
 * Pick up the root node of heap and put the end of container
*/
template<class RandomIter, class Distance, class T>
void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value) {
    // First precolate down
    auto topIndex = holeIndex;
    auto rchild = 2 * holeIndex + 2;
    while (rchild < len) {
        if (*(first + rchild) < *(first + rchild - 1)) {
            rchild--;
        }
        *(first + holeIndex) = *(first + rchild);
        holeIndex = rchild;
        rchild = 2 * (rchild + 1);
    }
    if (rchild == len) {
        // If there is no right child node
        *(first + holeIndex) = *(first + (rchild - 1));
        holeIndex = rchild - 1;
    }
    saberstl::push_heap_aux(first, holeIndex, topIndex, value);
}

template<class RandomIter, class Distance, class T>
void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, T value, Distance*) {
    // First move the root node to the end
    // Then adjust the elements in [first, last - 1), make them a new max-heap
    *result = *first;
    saberstl::adjust_heap(first, static_cast<Distance>(0), last - first, value);
}

template<class RandomIter>
void pop_heap(RandomIter first, RandomIter last) {
    saberstl::pop_heap_aux(first, last - 1, last - 1, *(last - 1), distance_type(first));
}

// Overload version
template<class RandomIter, class Distance, class T, class Compared>
void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value, Compared comp) {
    // First precolate down
    auto topIndex = holeIndex;
    auto rchild = 2 * holeIndex + 2;
    while (rchild < len) {
        if (comp(*(first + rchild), *(first + rchild - 1))) {
            rchild--;
        }
        *(first + holeIndex) = *(first + rchild);
        holeIndex = rchild;
        rchild = 2 * (rchild + 1);
    }
    if (rchild == len) {
        // If there is no right child node
        *(first + holeIndex) = *(first + (rchild - 1));
        holeIndex = rchild - 1;
    }
    saberstl::push_heap_aux(first, holeIndex, topIndex, value, comp);
}

template<class RandomIter, class Distance, class T, class Compared>
void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, T value, Distance*, Compared comp) {
    *result = *first;
    saberstl::adjust_heap(first, static_cast<Distance>(0), last - first, value, comp);
}

template<class RandomIter, class Compared>
void pop_heap(RandomIter first, RandomIter last, Compared comp) {
    saberstl::pop_heap_aux(first, last - 1, last - 1, *(last - 1), distance_type(first), comp);
}


/* ----------- sort_heap ----------- */
/*
 * The function pass two iters, represent the begin and end of a heap container.
 * Do the operation 'pop_heap' repeatedly, until the diff of start and end is 1
*/
template<class RandomIter>
void sort_heap(RandomIter first, RandomIter last) {
    // Each time do the 'pop_heap', the max element will move to the end of the heap
    // When there is only one element left, the sort is finish
    while (last - first > 1) {
        saberstl::pop_heap(first, last--);
    }
}

// Overloaded version
template<class RandomIter, class Compared>
void sort_heap(RandomIter first, RandomIter last, Compared comp) {
    while (last - first > 1) {
        saberstl::pop_heap(first, last--, comp);
    }
}

/* ----------- make_heap ----------- */
/*
 * The function pass two iters, represent the begin and end of a heap container.
 * Merge the elements into one heap
*/
template<class RandomIter, class Distance>
void make_heap_aux(RandomIter first, RandomIter last, Distance*) {
    if (last - first < 2) return;
    auto len = last - first;
    auto holeIndex = (len - 2) / 2;
    while (true) {
        // Rearrange the child tree with the root node is holeIndex
        saberstl::adjust_heap(first, holeIndex, len, *(first + holeIndex));
        if (holeIndex == 0) return;
        holeIndex--;
    }
}

template<class RandomIter>
void make_heap(RandomIter first, RandomIter last) {
    saberstl::make_heap_aux(first, last, distance_type(first));
}

// Overloaded version
template<class RandomIter, class Distance, class Compared>
void make_heap_aux(RandomIter first, RandomIter last, Distance*, Compared comp) {
    if (last - first < 2) return;
    auto len = last -first;
    auto holeIndex = (len - 2) / 2;
    while (true) {
        saberstl::adjust_heap(first, holeIndex, len, *(first + holeIndex), comp);
        if (holeIndex == 0) return;
        holeIndex--;
    }
}

template<class RandomIter, class Compared>
void make_heap(RandomIter first, RandomIter last, Compared comp) {
    saberstl::make_heap_aux(first, last, distance_type(first), comp);
}

} // namespace saberstl


#endif // !__SABERSTL_HEAP_ALHO_H__