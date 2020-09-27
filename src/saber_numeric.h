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

} // namespace saberstl

#endif // !__SABERSTL__NUMERIC_H__