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

} // namespace saberstl



#endif // !__SABERSTL__MEMORY_H_