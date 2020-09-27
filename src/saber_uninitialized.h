#ifndef SBAER_UNINITILALIZED_H
#define SBAER_UNINITILALIZED_H

#include "saber_util.h"
#include "saber_construct.h"
#include "saber_iterator.h"
#include "saber_type.h"
#include "saber_algobase.h"

namespace saberstl {

/* ---------------- uninitialized_copy ---------------- */
/*
 * Copy the element in range [first, last) to the space start with the result
 * Return the position of copy finished
*/
template<class InputIter, class ForwardIter>
ForwardIter unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::true_type) {
    return saberstl::copy(first, last, result);
}

template<class InputIter, class ForwardIter>
ForwardIter unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::false_type) {
    auto cur = result;
    try {
        for (; first != last; first++, cur++) {
            saberstl::construct(&*cur, *first);
        }
    } catch (...) {
        for (; result != cur; result++) {
            saberstl::destory(&*result);
        }
    }
    return cur;
}

template<class IntpuIter, class ForwardIter>
ForwardIter uninitialized_copy(IntpuIter first, IntpuIter last, ForwardIter result) {
    return saberstl::unchecked_uninit_copy(first, last, result, std::is_trivially_copy_assignable<
                                                                typename iterator_traits<ForwardIter>::
                                                                value_type>{});
}

} // namespace saberstl


#endif //!SBAER_UNINITILALIZED_H