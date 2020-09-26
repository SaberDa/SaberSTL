#ifndef __SABERSTL_SET_ALGO_H__
#define __SABERSTL_SET_ALGO_H__

#include "saber_algobase.h"
#include "saber_iterator.h"

namespace saberstl {

/* ----------- set_union ----------- */
/*
 * Calculate the S1 U S2, and store the result into the result.
 * Return an iter points the end of result
*/
template<class InputIter1, class InputIter2, class OutputIter>
OutputIter set_union(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            *result = *first1;
            first1++;
        } else if (*first1 > *first2) {
            *result = *first2;
            first2++;
        } else {
            *result = *first1;
            first1++, first2++;
        }
        result++;
    }
    return saberstl::copy(first2, last2, saberstl::copy(first1, last1, result));
}

// Overloaded version
template<class InputIter1, class InputIter2, class OutputIter, class Compared>
OutputIter set_union(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result, Compared comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first1, *first2)) {
            *result = *first1;
            first1++;
        } else if (comp(*first2, *first1)) {
            *result = *first2;
            first2++;
        } else {
            *result = *first1;
            first1++, first2++;
        }
        result++;
    }
    return saberstl::copy(first2, last2, saberstl::copy(first1, last1, result));
}


/* ----------- set_intersectino ----------- */
/*
 * Calculate the S1 ∩ S2, and store the result into the result.
 * Return an iter points the end of result
*/
template<class InputIter1, class InputIter2, class OutputIter>
OutputIter set_intersection(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) first1++;
        else if (*first1 > *first2) first2++;
        else {
            *result = *first1;
            first1++, first2++;
            result++;
        }
    }
    return result;
}


// Overloaded version
template<class InputIter1, class InputIter2, class OutputIter, class Compared>
OutputIter set_intersection(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result, Compared comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first1, *first2)) first1++;
        else if (comp(*first2, *first1)) first2++;
        else {
            *result = *first1;
            first1++, first2++;
            result++;
        }
    }
    return result;
}


/* ----------- set_difference ----------- */
/*
 * Calculate the S1 - S2, and store the result into the result.
 * Return an iter points the end of result
*/
template<class InputIter1, class InputIter2, class OutputIter>
OutputIter set_difference(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            *result = *first1;
            first1++;
            result++;
        } else if (*first1 > *first2) {
            first2++;
        } else {
            first1++, first2++;
        }
    }
    return saberstl::copy(first1, last1, result);
}

// Overloaded version
template<class InputIter1, class InputIter2, class OutputIter, class Compared>
OutputIter set_difference(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result, Compared comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first1, *first2)) {
            *result = *first1;
            first1++;
            result++;
        } else if (comp(*first2, *first1)) {
            first2++;
        } else {
            first1++, first2++;
        }
    }
    return saberstl::copy(first1, last1, result);
}


} // namespace saberstl


#endif // !__SABERSTL_SET_ALGO_H__