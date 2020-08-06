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

} // namespace saberstl

#endif