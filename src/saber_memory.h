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


/*
 * Class template: temporory_buffer
 * Application and release of temporary buffer zone
*/ 
template <class ForwardIterator, class T>
class temporary_buffer {
private:
    ptrdiff_t original_len;     // buffer allocated space
    ptrdiff_t len;              // buffer actually space
    T* buffer;                  // pointer to buffer
public:
    temporary_buffer(ForwardIterator first, ForwardIterator last);

    ~temporary_buffer() {
        saberstl::destory(buffer, buffer + len);
        free(buffer);
    }

public:
    ptrdiff_t size() const noexcept { return len; }
    ptrdiff_t request_size() const noexcept { return original_len; }
    T* begin() noexcept { return buffer; }
    T* end() noexcept { return buffer + len; }

private:
    void allocate_buffer();
    void initialize_buffer(const T&, std::true_type) {}
    void initialize_buffer(const T& value, std::false_type) {
        saberstl::uninitialized_fill_n(buffer, len, value);
    }

private:
    temporary_buffer(const temporary_buffer&);
    void operator=(const temporary_buffer&);
};


/*
 * construct function
*/
template <class ForwardIterator, class T>
temporary_buffer<ForwardIterator, T> ::
temporary_buffer(ForwardIterator first, ForwardIterator last) {
    try {
        len = saberstl::distance(first, last);
        allocate_buffer();
        if (len > 0) {
            initialize_buffer(*first, std::is_trivially_default_constructible<T>());
        }
    } catch (...) {
        free(buffer);
        buffer = nullptr;
        len = 0;
    }
}

} // namespace saberstl



#endif // !__SABERSTL__MEMORY_H_