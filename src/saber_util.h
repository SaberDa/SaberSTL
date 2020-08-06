#ifndef __SABER_UTIL_H
#define __SABER_UTIL_H

/*
 * This file contains some general tools
 * 
 * including functions such as move, forward, swap, and pair, etc.
*/

#include <cstddef>

#include "saber_type.h"

namespace saberstl {

/* ===================== Move ======================= */

template <class T>
typename std::remove_reference<T>::type&& move(T&& arg) noexcept {
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
}

/* ===================== Forward ======================= */

template <class T>
T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
    return static_cast<T&&>(arg);
}

template <class T>
T&& forward(typename std::remove_reference<T>::type&& arg) noexcept {
    static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
    return static_cast<T&&>(arg);
}

/* ===================== Swap ======================= */

template <class Tp>
void swap(Tp& lhs, Tp& rhs) {
    auto temp(saberstl::move(lhs));
    lhs = saberstl::move(rhs);
    rhs = saberstl::move(temp);
}

template <class ForwardIter1, class ForwardIter2>
ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2) {
    for (; first1 != last1; first1++, (void) first2++) saberstl::swap(*first1, *first2);
    return first2;
}

template <class Tp, size_t N>
void swap(Tp(&a)[N], Tp(&b)[N]) {
    saberstl::swap_range(a, a + N, b);
}

} // namespace saberstl

#endif