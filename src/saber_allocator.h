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
    static T* allocator();
    static T* allocator(size_type n);

    static void deallocator(T* ptr);
    static void deallocator(T* ptr, size_type n);

    static void construct(T* ptr);
    static void construct(T* ptr, const T& value);
    static void construct(T* ptr, T&& value);

    template<class... Args> 
    static void construct(T* ptr, Args&& ...args);

    static void destory(T* ptr);
    static void destory(T* first, T* last);
};



}; // namespace saberstl

#endif // !SABERSTL__ALLOCATOR_H