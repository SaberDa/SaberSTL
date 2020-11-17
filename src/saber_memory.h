#ifndef __SABERSTL__MEMORY_H_
#define __SABERSTL__MEMORY_H_

/*
 * This header file is responsible for more advanced dynamic memory management
*/

#include <cstddef>
#include <cstdlib>
#include <climits>

#include "saber_algobase.h"
#include "saber_allocator.h"
#include "saber_construct.h"
#include "saber_uninitialized.h"

namespace saberstl {

// Get object address
template <class Tp>
constexpr Tp* address_of(Tp& value) noexcept {
    return &value;
}

// Get/ Release temporary buffer
template <class T>
pair<T*, ptrdiff_t> get_buffer_helper(ptrdiff_t len, T*) {
    if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T))) {
        len = INT_MAX / sizeof(T);
    }
    while (len > 0) {
        T* tmp = static_cast<T*>(malloc(static_cast<size_t>(len) * sizeof(T)));
        if (tmp) {
            return pair<T*, ptrdiff_t>(tmp, len);
        }
        len /= 2;
    }
    return pair<T*, ptrdiff_t>(nullptr, 0);
}

template <class T>
pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len) {
    return get_buffer_helper(len, static_cast<T*>(0));
}

template <class T> 
pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len, T*) {
    return get_buffer_helper(len, static_cast<T*>(0));
}

template <class T>
void release_temporary_buffer(T* ptr) {
    free(ptr);
}

} // namespace saberstl



#endif // !__SABERSTL__MEMORY_H_