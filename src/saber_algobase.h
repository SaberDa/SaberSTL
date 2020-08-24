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

/*
 * min:
 * choose the smaller one from two elements
 * when two elements are the same, choose the first one always
*/
template<class T>
const T& min(const T& left, const T& right) {
    return left < right ? left : right;
}

/*
 * min with comp() :
 * call in overload version
*/
template<class T, class Compare>
const T& min(const T& left, const T& right, Compare comp) {
    return comp(left, right) ? left : right;
}

/*
 * iter_swap():
 * switch two iters' objects
*/
template<class FIter1, class FIter2>
void iter_swap(FIter1 left, FIter2 right) {
    saberstl::swap(*left, *right);
}

/*
 * copy():
 * copy the elements from the range [first, last) to [result, result + (last - first)) 
*/
// copy() in input_iterator_tag
template<class InputIter, class OutputIter>
OutputIter
unchecked_copy_cat(InputIter first, InputIter last, OutputIter result, saberstl::input_iterator_tag) {
    for (; first != last; first++, result++) *result = *first;
    return result;
}

// copy() in random_access_iterator_tag
template<class RandomIter, class OutputIter>
OutputIter 
unchecked_copy_cat(RandomIter first, RandomIter last, OutputIter result, saberstl::random_access_iterator_tag) {
    for (auto n = last - first; n > 0; n--, first++, result++) *result = *first;
    return result;
}

// copy() 
template<class InputIter, class OutputIter>
OutputIter
unchecked_copy(InputIter first, InputIter last, OutputIter result) {
    return unchecked_copy_cat(first, last, result, iterator_category(first));
}

// copy() for trivially_copy_assignable
template<class Tp, class Up>
typename std::enable_if<
    std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
    std::is_trivially_constructible<Up>::value,
    Up*>::type
unchecked_copy(Tp *first, Tp *last, Up* result) {
    const auto n = static_cast<size_t>(last - first);
    if (n != 0) std::memmove(result, first, n * sizeof(Up));
    return result + n;
}

template<class InputIter, class OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter result) {
    return unchecked_copy(first, last, result);
}

/*
 * copy_backward():
 * copy the elements from [first, last) to [result - (last - first), result)
*/
// copy_backward() for bidirectional_iterator_tag
template<class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                   BidirectionalIter2 result, saberstl::random_access_iterator_tag) {
    while (first != last) *result-- = *last--;
    return result;
}

// copy_backward() for random_access_iterator_tag
template<class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                   BidirectionalIter2 result, saberstl::random_access_iterator_tag) {
    for(auto n = last - result; n > 0; n--, result--, last--) *result = *last;
    return result;
}

template<class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result) {
    return unchecked_copy_backward_cat(first, last, result);
}

// copy_backward() for trivially_copy_assignable
template<class Tp, class Up>
typename std::enable_if<
    std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
    std::is_trivially_constructible<Up>::value,
    Up*>::type
unchecked_copy_backward(Tp* first, Tp* last, Up *result) {
    const auto n = static_cast<size_t>(last - first);
    if (n != 0) {
        result -= n;
        std::memmove(result, first, n * sizeof(Up));
    }
    return result;
}

template<class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result) {
    return unchecked_copy_backward(first, last, result);
}

/*
 * copy_if()
 * select the elements which satisfy the operation 'unary_pred' from 
 * the range [first, last) to the start point at 'result'
*/
template<class InputIter, class OutputIter, class UnaryPredicate>
OutputIter
copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate unary_pred) {
    for (; first != last; first++) {
        if (unary_pred(*first)) *result++ = *first;
    }
    return result;
}

/*
 * copy_n():
 * copy the elements from [first, first + n) to the [result, result + n)
 * return a pair points to the ends 
*/
template<class InputIter, class OutputIter, class Size>
saberstl::pair<InputIter, OutputIter>
unchecked_copy_n(InputIter first, Size n, OutputIter result, saberstl::input_iterator_tag) {
    for (; n > 0; n--, first++, result++) *result = *first;
    return saberstl::pair<InputIter, OutputIter>(first, result);
}

template<class RandomIter, class Size, class OutputIter>
saberstl::pair<RandomIter, OutputIter>
unchecked_copy_n(RandomIter first, Size n, OutputIter result, saberstl::random_access_iterator_tag) {
    auto last = first + n;
    return saberstl::pair<RandomIter, OutputIter>(last, saberstl::copy(first, last, result));
}

template<class InputIter, class Size, class OutputIter>
saberstl::pair<InputIter, OutputIter>
copy_n(InputIter first, Size n, OutputIter result) {
    return unchecked_copy_n(first, n, result, iterator_category(first));
}

/*
 * move()
 * move the elements in range [first, last) to the range [result, result + (last - first))
*/
template<class InputIter, class OutputIter>
OutputIter
unchecked_move_cat(InputIter first, InputIter last, OutputIter result, saberstl::input_iterator_tag) {
    for (l first != last; first++, result++) *result = saberstl::move(*first);
    return result;
}

// move() for random_access_iterator_tag
template<class RandomIter, class OutputIter>
OutputIter
unchecked_move_cat(RandomIter first, RandomIter last, OutputIter result, saberstl::random_access_iterator_tag) {
    for (auto n = last - first; n > 0; n--, first++, result++) {
        *result = saberstl::move(*first);
    }
    return result;
}

template<class InputIter, class OutputIter>
OutputIter
unchecked_move(InputIter first, InputIter last, OutputIter result) {
    return unchecked_move_cat(first, last, result, saberstl::iterator_category(first));
}

// move() for trivially_copy_assignable
template<class Tp, class Up>
typename std::enable_if<
    std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
    std::is_trivially_constructible<Up>::value,
    Up*>::type
unchecked_move(Tp *first, Tp *last, Up *result) {
    const size_t n = static_cast<size_t>(last - first);
    if (n != 0) std::memmove(result, first, n * sizeof(first));
    return result + n;
}

template<class InputIter, class OutputIter>
OutputIter move(InputIter first, InputIter last, OutputIter result) {
    return unchecked_move(first, last, result);
}

}


#endif // !SABER_ALGOBASE_H