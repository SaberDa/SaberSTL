#ifndef __SABERSTL__NUMERIC_H__
#define __SABERSTL__NUMERIC_H__

#include "saber_iterator.h"

namespace saberstl {

/* --------------- accumulate --------------- */
/*
 * Version 1: Accumulate each element with the initial value init
 * Version 2: Do the binary operation on each element whit the initial value init
*/
// Version 1
template <class InputIter, class T>
T accumulate(InputIter first, InputIter last, T init) {
    for (; first != last; first++) {
        init += *first;
    }
    return init;
}

// Version 2
template<class InputIter, class T, class BinaryOp>
T accumulate(InputIter first, InputIter last, T init, BinaryOp binary_op) {
    for (; first != last; first++) {
        init = binary_op(init, *first);
    }
    return init;
}

/* --------------- adjacent_difference --------------- */
/*
 * Version 1: Calculate the adjacent elements' diff, and store at the range begin with result
 * Version 2: Do the binary operation on the adjacent elements
*/
// Version 1
template <class InputIter, class OutputIter> 
OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result) {
    if (first == last) return result;
    // Recode the first element
    *result = *first;
    auto value = *first;
    while (++first != last) {
        auto temp = *first;
        *++result = temp - value;
        value = temp;
    }
    return ++result;
}

// Version 2
template <class InputIter, class OutputIter, class BinaryOp>
OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result, BinaryOp binary_op) {
    if (first == last) return result;
    // Recode the first element
    *result = *first;
    auto value = *first;
    while (++first != last) {
        auto temp = *first;
        *++result = binary_op(temp, value);
        value = temp;
    }
    return ++result;
}


/* --------------- inner_product --------------- */
/*
 * Version 1: Calculate the inner product between two ranges with the initial value is init
 * Version 2: Overloaded operator+ and operator*
*/
// Version 1
template <class InputIter1, class InputIter2, class T>
T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init) {
    for (; first1 != last1; first1++, first2++) {
        init = init + (*first1 * *first2)
    }
    return init;
}

// Version 2
template <class InputIter1, class InputIter2, class T, class BinaryOp1, class BinaryOp2>
T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init, BinaryOp1 binary_op1, BinaryOp2 binary_op2) {
    for (; first1 != last1; first1++, first2++) {
        init = binary_op1(init, binary_op2(*first1, *first2));
    }
    return init;
}


/* --------------- iota --------------- */
/*
 * Fill the elements in range [first, last) with the initial value init
*/ 
template<class ForwardIter, class T>
void iota(ForwardIter first, ForwardIter last, T value) {
    while (first != last) {
        *first++ = value;
        value++;
    }
}

} // namespace saberstl

#endif // !__SABERSTL__NUMERIC_H__