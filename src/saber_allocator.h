#ifndef SABERSTL__ALLOCATOR_H
#define SABERSTL__ALLOCATOR_H

/*
 * The template class 'allocator'
 * To manage memory's alloc and free, 
 * And to manage the object's construction, destruction
*/

#include "saber_construct.h"
#include "saber_util.h"

namespace saberstl {

/*
 * Template class: allocator
*/ 
template <class T>
class allocator {
public:
    typedef T           value_type;
    typedef T*          pointer;
    typedef const T*    const_pointer;
    typedef T&          reference;
    typedef const T&    const_reference;
    typedef size_t      size_type;

public:
    static T* allocate();
    static T* allocate(size_type n);

    static void deallocate(T* ptr);
    static void deallocate(T* ptr, size_type n);

    static void construct(T* ptr);
    static void construct(T* ptr, const T& value);
    static void construct(T* ptr, T&& value);

    template<class... Args> 
    static void construct(T* ptr, Args&& ...args);

    static void destory(T* ptr);
    static void destory(T* first, T* last);
};

template<class T>
T* allocator<T>::allocate() {
    return static_cast<T*>(::operator new(sizeof(T)));
}

template<class T>
T* allocator<T>::allocate(size_type n) {
    if (n == 0) return nullptr;
    return static_cast<T*>(::operator new(n * sizeof(T)));
}

template<class T>
void allocator<T>::deallocate(T* ptr) {
    if (ptr == nullptr) return;
    ::operator delete(ptr);
}

template<class T>
void allocator<T>::deallocate(T* ptr, size_type /*size*/) {
    if (ptr == nullptr) return;
    ::operator delete(ptr);
}

template<class T>
void allocator<T>::construct(T* ptr) {
    saberstl::construct(ptr);
}

template<class T>
void allocator<T>::construct(T* ptr, const T& value) {
    saberstl::construct(ptr, value);
}

template<class T>
void allocator<T>::construct(T* ptr, T&& value) {
    saberstl::construct(ptr, saberstl::move(value));
}

template<class T>
template<class ...Args>
void allocator<T>::construct(T* ptr, Args&& ...args) {
    saberstl::construct(ptr, saberstl::forward<Args>(args)...);
}

template<class T>
void allocator<T>::destory(T* ptr) {
    saberstl::destory(ptr);
}

template<class T>
void allocator<T>::destory(T* first, T* last) {
    saberstl::destory(first, last);
}

}; // namespace saberstl

#endif // !SABERSTL__ALLOCATOR_H