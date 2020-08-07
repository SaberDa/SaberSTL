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

/* ===================== PAIR ======================= */

/*
 * struct template: pair
 * Two parameters present two types of data
 * Use 'first' and 'second' to get the first data and second data
*/
template <class Ty1, class Ty2>
struct pair {
    typedef Ty1     first_type;
    typedef Ty2     second_type;

    first_type first;           // To store the first value
    second_type second;         // To store the second value

    // default constructiable
    template <class Other1 = Ty1, class Other2 = Ty2, 
        typename = typename std::enable_if<
            std::is_default_constructible<Other1>::value &&
            std::is_default_constructible<Other2>::value, void>::type>
        constexpr pair() : first(), second() {
    }

    // implicit constructiable for this type
    template <class U1 = Ty1, class u2 = Ty2,
        typename std::enable_if<
            std::is_copy_constructible<U1>::value &&
            std::is_copy_constructible<U2>::value &&
            std::is_convertible<const U1&, Ty1>::value &&
            std::is_convertible<const U2&, Ty2>::value, int>::type = 0>
        constexpr pair(const Ty1& a, const Ty2& b) : first(a), second(b) {
    }

    // explicit constructible for this type
    template <class U1 = Ty1, class u2 = Ty2,
        typename std::enable_if<
            std::is_copy_constructible<U1>::value &&
            std::is_copy_constructible<U2>::value &&
            (!std::is_convertible<const U1&, Ty1>::value ||
            !std::is_convertible<const U2&, Ty2>::value), int>::type = 0>
        constexpr pair(const Ty1& a, const Ty2& b) : first(a), second(b) {
    }

    pair(const pair& rhs) = default;
    pair(pair&& rhs) = default;

    // implicit constructiable for other type
    template <class Other1, class Other2,
        typename std::enable_if<
            std::is_constructible<Ty1, Other1>::value &&
            std::is_constructible<Ty2, Other2>::value &&
            std::is_convertible<Other1&&, Ty1>::value &&
            std::is_convertible<Other2&&, Ty2>::value, int>::type = 0>
        constexpr pair(Other1&& a, Other2&& b) :
            first(saberstl::forward<Other1>(a)),
            second(saberstl::forward<Other2>(b)) {
    }

    // explicit constructiable for other type
    template <class Other1, class Other2,
        typename std::enable_if<
            std::is_constructible<Ty1, Other1>::value &&
            std::is_constructible<Ty2, Other2>::value &&
            (!std::is_convertible<Other1, Ty1>::value ||
             !std::is_convertible<Other2, Ty2>::value), int>::type = 0>
        explicit constexpr pair(Other1&& a, Other2&& b) :
            first(saberstl::forward<Other1>(a)),
            second(saberstl::forward<Other2>(b)) {
    }

    // implicit constructiable for other pair
    template <class Other1, class Other2,
        typename std::enable_if<
            std::is_constructible<Ty1, const Other1&>::value &&
            std::is_constructible<Ty2, const Other2&>::value &&
            std::is_convertible<const Other1&, Ty1>::value &&
            std::is_convertible<const Other2&, Ty2>::value, int>::type = 0>
        constexpr pair(const pair<Other1, Other2>& other) :
            first(other.first), second(other.second) {
    }

    // explicit constructiable for other pair
    template <class Other1, class Other2,
        typename std::enable_if<
            std::is_constructible<Ty1, const Other1&>:: value &&
            std::is_constructible<Ty2, const Other2&>::value &&
            (!std::is_convertible<const Other1&, Ty1>::value ||
             !std::is_convertible<const Other2&, Ty2>::value), int>::type = 0>
        explicit constexpr pair(const pair<Other1, Other2>& other) :   
            first(other.first), second(other.second) {
    }
    
    // implicit constructiable for other pair
    template <class Other1, class Other2,
        typename std::enable_if<
            std::is_constructible<Ty1, Other1>::value &&
            std::is_constructible<Ty2, Other2>::value &&
            std::is_convertible<Other1, Ty1>::value &&
            std::is_convertible<Other2, Ty2>::value, int>::type = 0>
        constexpr pair(pair<Other1, Other2>&& other) :
            first(saberstl::forward<Other1>(other.first)),
            second(saberstl::forward<Other2>(other.second)) {
    }
    

    // explicit constructiable for other pair
    template <class Other1, class Other2,
        typename std::enable_if<
            std::is_constructible<Ty1, Other1>::value &&
            std::is_constructible<Ty2, Other2>::value &&
            (!std::is_convertible<Other1, Ty1>:: value ||
             !std::is_convertible<Other2, Ty2>::value), int>::type = 0>
        explicit constexpr pair(pair<Other1, Other2>&& other) :
            first(saberstl::forward<Other1>(other.first)),
            second(saberstl::forward<Other2>(other.second)) {
    }


    // copy assign for this pair
    pair& operator=(const pair& rhs) {
        if (this != &rhs) {
            first = rhs.first;
            second = rhs.second;
        }
        return *this;
    }

    // move assign for this pair
    pair& operator=(pair&& rhs) {
        if (this != &rhs) {
            first = saberstl::forward(rhs.first);
            second = saberstl::forward(rhs.second);
        }
        return *this;
    }

    // copy assign for other pair
    template <class T1, class T2>
    pair& operator=(const pair<T1, T2>& other) {
        first = other.first;
        second = other.second;
        return *this;
    }

    // move assign for other pair
    template <class Other1, class Other2>
    pair& operator=(pair<Other1, Other2>&& other) {
        first = saberstl::forward<Other1>(other.first);
        second = saberstl::forward<Other2>(other.second);
        return *this;
    }

    ~pair() = default;

    void swap(pair& other) {
        if (this != &other) {
            saberstl::swap(first, other.first);
            saberstl::swap(second, other.second);
        }
    }
};

/* ===================== Operator Overloading ======================= */

template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs == rhs);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return rhs < lhs;
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs > rhs);
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs < rhs);
}

// overload saberstl::swap
template <class T1, class T2>
void swap(pair<T1, T2>& lhs, pair<T1, T2>& rhs) {
    lhs.swap(rhs);
}

// global function: make_pair
template <class T1, class T2>
pair<T1, T2> make_pair(T1&& first, T2&& second) {
    return pair<T1, T2>(saberstl::forward<T1>(first), saberstl::forward<T2>(second));
}

} // namespace saberstl

#endif