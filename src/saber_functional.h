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

} // namespace saberstl

#endif // !__SABERSTL__FUNCTIONAL_H_