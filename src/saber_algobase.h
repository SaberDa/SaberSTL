#ifndef SABER_ALGOBASE_H
#define SABER_ALGOBASE_H

/*
 * The basic algorithm of saberstl
*/

#include <cstring>

#include "saber_iterator.h"
#include "saber_util.h"

namespace saberstl {

#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min

/*
 * max :
 * choose the bigger one from two elements.
 * when two elements are the same, choose the first one always
*/
template<class T>
const T& max(const T& left, const T& right) {
    return left < right ? right : left;
}

/*
 * max with comp() :
 * call in overload version
*/
template<class T, class Compare>
const T& max(const T& left, const T& right, Compare comp) {
    return comp(left, right) ? right : left;
}



}


#endif // !SABER_ALGOBASE_H