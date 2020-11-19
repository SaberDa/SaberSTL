#ifndef __SABERSTL__FUNCTIONAL_H_
#define __SABERSTL__FUNCTIONAL_H_

#include <cstddef>

namespace saberstl {

template <class Arg, class Result>
struct unarg_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

template <class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};


// Function object: PLUS
template <class T>
struct plus : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x + y; }
};

// Function object: MINUS
template <class T>
struct minus : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x - y; }
};

// Function object: MULTIPLIES
template <class T>
struct multiples : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x * y; }
};

// Function object: DIVIDES
template <class T>
struct divides : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x / y; }
};

// Function object: MODULES
template <class T>
struct modules : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x % y; }
};

// Function object: NEGATE
template <class T>
struct megate : public unarg_function<T, T> {
    T operator()(const T &x) const { return -x; }
};

template <class T>
T identity_element(plus<T>) { return T(0); }

template <class T>
T identity_element(multiples<T>) { return T(1); }

// Function Object: EQUAL_TO
template <class T>
struct equal_to : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x == y; }
};

// Function object: NOT_EQUAL_TO
template <class T>
struct not_equal_to : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x != y; }
};

// Function object: GREATER
template <class T>
struct greater : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x > y; }
};

// Function object: LESS
template <class T>
struct less : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x < y; }
};

// Function object: GREATER_EQUAL
template <class T>
struct greater_equal : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x >= y; }
};

// Function object: LESS_EQUAL
template <class T>
struct less_equal : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x <= y; }
};

// Function object: LOGICAL_AND
template <class T>
struct logical_and : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x && y; }
};

// Function object: LOGICAL_OR
template <class T>
struct logical_or : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const { return x || y; }
};


// Function object: LOGICAL_NOT
template <class T>
struct logical_not : public unarg_function<T, T> {
    T operator()(const T &x) const { return !x; }
};

template <class T>
struct identity : public unarg_function<T, T> {
    const T& operator()(const T &x) const { return x; }
};

// Select function: receive a pair, return the first element
template <class Pair>
struct selectfirst : public unarg_function<Pair, typename Pair::first_type> {
    const typename Pair::first_type& operator()(const Pair &x) const {
        return x.first;
    }
};

// Select function: receive a pair, return the second element
template <class Pair>
struct selectsecond : public unarg_function<Pair, typename Pair::second_type> {
    const typename Pair::second_type& operator()(const Pair &x) const {
        return x.second;
    }
};

} // namespace saberstl

#endif // !__SABERSTL__FUNCTIONAL_H_