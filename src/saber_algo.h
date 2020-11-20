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
 * Check if all elements in range [first, last) satifires 'unary_pred' are 'true'
 * If they are, return true
*/
template <class InputIter, class UnaryPredicate>
bool all_of(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    for (; first != last; first++) {
        if (!unary_pred(*first)) return false;
    }
    return true;
}

}

#endif // !__SABERSTL__ALGO_H_