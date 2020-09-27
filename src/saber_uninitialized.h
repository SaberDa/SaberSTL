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

/* ---------------- uninitialized_copy_n ---------------- */
/*
 * Copy the element in range [first, first + n) to the space start with the result
 * Return the position of copy finished
*/
template<class InputIter, class ForwardIter, class Size>
ForwardIter unchecked_uninit_copy_n(InputIter first, Size n, ForwardIter result, std::true_type) {
    return saberstl::copy_n(first, n, result).second;
}

template<class InputIter, class ForwardIter, class Size>
ForwardIter unchecked_uninit_copy_n(InputIter first, Size n, ForwardIter result, std::false_type) {
    auto cur = result;
    try {
        for (; n > 0; n--, first++, cur++) {
            saberstl::construct(&*cur, first);
        }
    } catch (...) {
        for (; result != cur; result++) {
            saberstl::destory(&*result);
        }
    }
    return cur;
}

template<class InputIter, class ForwardIter, class Size>
ForwardIter uninitialized_copy_n(InputIter first, Size n, ForwardIter result) {
    return saberstl::unchecked_uninit_copy_n(first, n, result,
                                             std::is_trivially_copy_assignable<
                                             typename iterator_traits<InputIter>::
                                             value_type>{});
}


/* ---------------- uninitialized_fill ---------------- */
/*
 * Fill the elements in range [first, last)
*/
template<class ForwardIter, class T>
void unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::true_type) {
    saberstl::fill(first, last, value);
}

template<class ForwardIter, class T>
void unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::false_type) {
    auto cur = first;
    try {
        for (; cur != last; cur++) {
            saberstl::construct(&*cur, value);
        }
    } catch (...) {
        for (; first != cur; first++) {
            saberstl::destory(&*first);
        }
    }
}

template<class ForwardIter, class T>
void uninitialized_fill(ForwardIter first, ForwardIter last, const T& value) {
    saberstl::unchecked_uninit_fill(first, last, value
                                    std::is_trivially_copy_assignable<
                                    typename iterator_traits<ForwardIter>::
                                    value_type>{});
}


/* ---------------- uninitialized_fill_n ---------------- */
/*
 * Fill the elements in range [first, first + n)
*/
template<class ForwardIter, class Size, class T>
ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::true_type) {
    return saberstl::fill_n(first, n, value);
}

template<class ForwardIter, class Size, class T>
ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::false_type) {
    auto cur = first;
    try {
        for (; n > 0; n--, cur++) {
            saberstl::construct(&*cur, value);
        }
    } catch (...) {
        for (; first != cur; first++) {
            saberstl::destory(&*first);
        }
    }
    return cur;
}

template<class ForwardIter, class T, class Size>
void uninitialized_fill_n(ForwardIter first, Size n, const T& value) {
    saberstl::unchecked_uninit_fill(first, n, value
                                    std::is_trivially_copy_assignable<
                                    typename iterator_traits<ForwardIter>::
                                    value_type>{});
}


/* ---------------- uninitialized_move ---------------- */
/*
 * Move the element from [first, last) to the result
*/
template<class InputIter, class ForwardIter>
ForwardIter unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::true_type) {
    return saberstl::move(first, last, result);
}

template<class InputIter, class ForwardIter>
ForwardIter unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::false_type) {
    auto cur = first;
    try {
        for (; first != last; first++, cur++) {
            saberstl::construct(&*cur, saberstl::move(*first));
        }
    } catch (...) {
        saberstl::destory(result, cur);
    }
    return cur;
}

template<class InputIter, class ForwardIter>
ForwardIter uninitialized_move(InputIter first, InputIter last, ForwardIter result) {
    return saberstl::unchecked_uninit_move(first, last, result,
                                           std::is_trivially_copy_assignable<
                                           typename iterator_traits<InputIter>::
                                           value_type>{});
}

} // namespace saberstl


#endif //!SBAER_UNINITILALIZED_H