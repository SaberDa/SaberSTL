#ifndef __SABERSTL__ALGO_H_
#define __SABERSTL__ALGO_H_

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4244)
#endif

#include <cstddef>
#include <ctime>

#include "saber_algobase.h"
#include "saber_memory.h"
#include "saber_heap_algo.h"
#include "saber_functional.h"

namespace saberstl {

/*
 * all_of
 * Check if all elements in range [first, last) satisfies unary operation 'unary_pred' are 'true'
 * If they are, return true
*/
template <class InputIter, class UnaryPredicate>
bool all_of(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    for (; first != last; first++) {
        if (!unary_pred(*first)) return false;
    }
    return true;
}

/*
 * any_of
 * Check if there is one element in range [first, last) satisfies unary operation 'unary_pred' is true
 * If there is, return true
*/
template <class InputIter, class UnaryPredicate>
bool any_of(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    for (; first != last; first++) {
        if (unary_pred(*first)) return true;
    }
    return false;
}

/*
 * none_of
 * Check if all the elements in range [first, last) are not satisfy unary operation 'unary_pred' are false
 * If they are, return true
*/
template <class InputIter, class UnaryPredicate>
bool noneof(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    for (; first != last; first++) {
        if (unary_pred(*first)) return false;
    }
    return true;
}

/*
 * count
 * Compare the elements' value which in range [first, last) with the given value. Default use 'operator=='
 * Return the number of equal elements
*/
template <class InputIter, class T> 
size_t count(InputIter first, InputIter last, const T& value) {
    size_t n = 0;
    for (; first != last; first++) {
        if (*first == value) n++;
    }
    return n;
}

/*
 * count_if
 * Do unary operation for all the elements in range [first, last).
 * Return the number of elements which result is true
*/
template <class InputIter, class UnaryPredicate>
size_t count_if(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    size_t n = 0;
    for (; first != last; first++) {
        if (unary_pred(*first)) n++;
    }
    return n;
}

/*
 * find
 * Find the elements in range [first, last) which value equals to the given value
 * return the iterator which points to the result element
*/
template <class InputIter, class T> 
InputIter find(InputIter first, InputIter last, const T& value) {
    while(first != last && *first != value) first++;
    return first;
}

/*
 * find_if
 * Find the first element in range [first, last) which satisfies the unary operation 'unary_pred' is true
 * return the iterator which points to this element
*/
template <class InputIter, class UnaryPredicate>
InputIter find_if(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    while (first != last && !unary_pred(*first)) first++;
    return first;
}

}

#endif // !__SABERSTL__ALGO_H_