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

/*
 * find_if_not
 * Find the first element in range [first, last) which satisfies the unary operation 'unary_pred' is false
 * return the iterator which points to this element
*/ 
template <class InputIter, class UnaryPredicate>
InputIter find_if_not(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    while (first != last && unary_pred(*first)) first++;
    return first;
}

/*
 * search
 * Find the range [first2, last2) first appear point in range [first1, last1)
*/
template <class ForwardIter1, class ForwardIter2>
ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2) {
    auto d1 = saberstl::distance(first1, last1);
    auto d2 = saberstl::distance(first2, last2);
    if (d1 < d2) return last1;
    auto current1 = first1;
    auto current2 = first2;
    while (current2 != last2) {
        if (*current1 == *current2) {
            current1++;
            current2++;
        } else {
            if (d1 == d2) return last1;
            else {
                current1 = ++first1;
                current2 = first2;
                --d1;
            }
        }
    }
    return first1;
}

// Overload version, use the 'comp' as the compare function
template <class ForwardIter1, class ForwardIter2, class Compared>
ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, Compared comp) {
    auto d1 = saberstl::distance(first1, last1);
    auto d2 = saberstl::distance(first2, last2);
    if (d1 < d2) return last1;
    auto current1 = first1;
    auto current2 = first2;
    while (current2 != last2) {
        if (comp(*current1, *current2)) {
            current1++;
            current2++;
        } else {
            if (d1 == d2) return last1;
            else {
                current1 = ++ first1;
                current2 = first2;
                d1--;
            }
        }
    }
    return first1;
}

/*
 * search_n
 * Find the subsequence which components with n 'value' in the range [first, last)
 * return the iterator which points to the begin of the subsequence
*/
template <class ForwardIter, class Size, class T>
ForwardIter search_n(ForwardIter first, ForwardIter last, Size n, const T& value) {
    if (n <= 0) return first;
    first == saberstl::find(first, last, value);
    while (first != last) {
        auto m = n - 1;
        auto i = first;
        i++;
        while (i != last && m != 0 && *i == value) {
            i++;
            m--;
        }
        if (m == 0) return first;
        else first = saberstl::find(i, last, value);
    }
    return last;
}

// Overload version, use the 'comp' as the compare function
template <class ForwardIter, class Size, class T, class Compared>
ForwardIter search_n(ForwardIter first, ForwardIter last, Size n, const T& value, Compared comp) {
    if (n <= 0) return first;
    while (first != last) {
        if (comp(*first, value)) break;
        first++;
    }
    while (first != last) {
        auto m = n - 1;
        auto i = first;
        i++;
        while (i != last && m != 0 && comp(*i, value)) {
            i++;
            m--;
        }
        if (m == 0) return first;
        else {
            while (i != last) {
                if (comp(*i, value)) break;
                i++;
            }
            first = i;
        }
    }
    return last;
}

}

#endif // !__SABERSTL__ALGO_H_