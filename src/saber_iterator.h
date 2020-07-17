#ifndef __SABER_ITERATOR_H__
#define __SABER_ITERATOR_H__

/* 
 * For iterator design and 
 * contains some template structures 
 * and global functions.
*/

#include <cstddef>

#include "saber_type.h"

namespace saberstl {

/* Five types of iterator */
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/* Iterator template */
template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator {
    typedef Category    iterator_category;
    typedef T           value_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
    typedef Distance    difference_type;
};

} // namespace saberstl

#endif // SABER_ITERATOR_H__