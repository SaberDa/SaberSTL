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

// Hash Object

template <class Key>
struct hash {};

template <class T>
struct hash<T*> {
    size_t operator()(T* p) const noexcept {
        return reinterpret_cast<size_t>(p);
    }
};

#define SBAERSTL_TRIVIAL_HASH_FCN(Type) \
template <> struct hash<Type> { \
size_t operator()(Type val) const noexcept { \
    return static_cast<size_t>(val); \
    } \
}; \

SBAERSTL_TRIVIAL_HASH_FCN(bool)

SBAERSTL_TRIVIAL_HASH_FCN(char)

SBAERSTL_TRIVIAL_HASH_FCN(signed char)

SBAERSTL_TRIVIAL_HASH_FCN(unsigned char)

SBAERSTL_TRIVIAL_HASH_FCN(wchar_t)

SBAERSTL_TRIVIAL_HASH_FCN(char16_t)

SBAERSTL_TRIVIAL_HASH_FCN(char32_t)

SBAERSTL_TRIVIAL_HASH_FCN(short)

SBAERSTL_TRIVIAL_HASH_FCN(unsigned short)

SBAERSTL_TRIVIAL_HASH_FCN(int)

SBAERSTL_TRIVIAL_HASH_FCN(unsigned int)

SBAERSTL_TRIVIAL_HASH_FCN(long)

SBAERSTL_TRIVIAL_HASH_FCN(unsigned long)

SBAERSTL_TRIVIAL_HASH_FCN(long long)

SBAERSTL_TRIVIAL_HASH_FCN(unsigned long long)

#undef SBAERSTL_TRIVIAL_HASH_FCN

inline size_t bitwise_hash(const unsigned char* first, size_t count) {
#if (_MSC_VER && _WIN64) || ((__GNUC__ || __clang__) &&__SIZEOF_POINTER__ == 8)
    const size_t fnv_offset = 14695981039346656037ull;
    const size_t fnv_prime = 1099511628211ull;
#else 
    const size_t fnv_offset = 2166136261u;
    const size_t fnv_prime = 16777619u;
#endif
    size_t result = fnv_offset;
    for (size_t i = 0; i < count; i++) {
        result ^= (size_t)first[i];
        result *= fnv_prime;
    }
    return result;
}

template<>
struct hash<float> {
    size_t operator()(const float& val) {
        return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(float));
    }
};

template<>
struct hash<double> {
    size_t operator()(const double &val) {
        return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(double));
    }
};

template<>
struct hash<long double> {
    size_t operator()(const long double &val) {
        return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(long double));
    }
};

} // namespace saberstl

#endif // !__SABERSTL__FUNCTIONAL_H_