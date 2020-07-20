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

};


#endif