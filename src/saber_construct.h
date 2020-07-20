#ifndef __SABER_CONSTRUCT_H__
#define __SABER_CONSTRUCT_H__

/*
 * This header file contains two functions construct, destroy
 * 
 * construct: responsible for the construction of the object
 * destroy: responsible for the destruction of the object
*/

#include <new>

#include "saber_type.h"
#include "saber_iterator.h"
#include "saber_util.h"

#ifdef _SABER_MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100)  // unused parameter
#endif // _SABER_MSC_VER

namespace saberstl {

    /* ================ Construct: construct the object ================== */

    template <class T> 
    void construct(T* ptr) {
        ::new ((void*)ptr) T();
    }

    template <class T, class U>
    void construct(T *ptr, const U& value) {
        ::new ((void*)ptr) T(value);
    }

    template <class T, class... Args>
    void construct(T *ptr, Args&&... args) {
        ::new ((void*)ptr) T(saberstl::forward<Args>(args)...);
    }



    /* ================ Destory: destory the object ================== */

    template <class T>
    void destory_one(T*, std::true_type) {}

    template <class T>
    void destory_one(T* pointer, std::false_type) {
        if (pointer != nullptr)
            pointer->~T();
    }

    template <class ForwardIter>
    void destory_cat(ForwardIter, ForwardIter, std::true_type) {}

    template <class ForwardIter>
    void destory_cat(ForwardIter first, ForwardIter last, std::false_type) {
        for (; first != last; first++) 
            destory(&*first);
    }

    template <class T>
    void destory(T *pointer) {
        destory_one(pointer, std::is_trivially_destructible<T>{});
    }

    template <class ForwardIter>
    void destory(ForwardIter first, ForwardIter last) {
        destory_cat(first, last, std::is_trivially_destructible<
                    typename iterator_traits<ForwardIter>::value_type>{});
    }
} // namespace saberstl




#endif