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

/*
 * move_backward
 * move the elements from [first, last) to the [result - (last - first), result)
*/

// bidirectional_iterator_tag version
template<class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2 
unchecked_move_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                            BidirectionalIter2 result, saberstl::bidirectional_iterator_tag) {
    while (first != last) *--result = saberstl::move(*--last);
    return result;
}

// random_access_iterator_tag version
template<class RandomIter1, class RandomIter2>
RandomIter2
unchecked_copy_backward_cat(RandomIter1 first, RandomIter1 last,
                            RandomIter2 result, saberstl::random_access_iterator_tag) {
    for (auto n = last - first; n > 0; n--) {
        *--result = saberstl::move(*--last);
    }
    return result;
}

template<class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_move_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result) {
    return unchecked_copy_backward_cat(first, last, result, iterator_category(first));
}

// specific version for trivially_copy_assignable
template<class Tp, class Up>
typename std::enable_if<
    std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
    std::is_trivially_move_assignable<Up>::value,
    Up*>::type
unchecked_move_backward(Tp *first, Tp *last, Up *result) {
    const size_t n = static_cast<size_t>(last - first);
    if (n != 0) {
        result -= n;
        std::memmove(result, first, n * sizeof(Up));
    }
    return result;
}

template<class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
move_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result) {
    return unchecked_move_backward(first, last, result);
}

/* ------- Equal ------- */
/*
 * Compare the first value in the [first, last) is equal to the second value or not.
*/
template<class InputIter1, class InputIter2>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2) {
    for (; first1 != last1; first1++, first2++) {
        if (*first1 != !first2) return false;
    }
    return true;
}

// Overload version, use the 'comp' to replace the compare operation
template<class InputIter1, class InputIter2, class Compared>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, Compared comp) {
    for (; first1 != last1; first1++, first2++) {
        if (!comp(*first1, *first2)) return false;
    }
    return true;
}


/* ------- Fill n ------- */
/*
 * Fill n value from the position 'first'
*/
template<class OutputIter, class Size, class T>
OutputIter unchecked_fill_n(OutputIter first, Size n, const T& value) {
    for (; n > 0; --n, first++) {
        *first = value;
    }
    return first;
}

// Specific version for one-byte
template<class Tp, class Size, class Up>
typename std::enable_if<
    std::is_integral<Tp>::value && sizeof(Tp) == 1 &&
    !std::is_same<Tp, bool>::value &&
    std::is_integral<Up>::value && sizeof(Up) == 1,
    Tp*>::type
unchecked_fill_n(Tp *first, Size n, Up value) {
    if (n > 0) std::memset(first, (unsigned char)value, (size_t)(n));
    return first + n;
}

template<class OutputIter, class Size, class T>
OutputIter fill_n(OutputIter first, Size n, const T& value) {
    return unchecked_fill_n(first, n,value);
}



/* ------- Fill ------- */
/*
 * Fill the new value in the range [first, last)
*/
template<class ForwardIter, class T>
void fill_cat(ForwardIter first, ForwardIter last, const T& value, saberstl::forward_iterator_tag) {
    for (; first != last; first++) {
        *first = value;
    }
}

template<class RandomIter, class T> 
void fill_cat(RandomIter first, RandomIter last, const T& value, saberstl::random_access_iterator_tag) {
    fill_n(first, last - first, value);
}

template<class ForwardIter, class T>
void fill(ForwardIter first, ForwardIter last, const T& value) {
    fill_cat(first, last, value, iterator_category(first));
}

/* ----------------- Lexicographical Compare ----------------- */
/*
 * Compare two lists in lexicographical order.
 * The different situation:
 * 1. If the first list's element is smaller, return true
 * 2. If the first list has no left but the second one has, return true
 * 3. If the second list has no left but the first one has, return false
 * 4. If both of the two lists has no left, return false
*/

template<class InputIter1, class InputIter2>
bool lexicographical_compare(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2) {
    for (; first1 != last1 && first2 != last2; first1++, first2++) {
        if (*first1 < *first2) return true;
        if (*first1 > *first2) return false;
    }
    return first1 == last1 && first2 != last2;
}

// Overloaded version
template<class InputIter1, class InputIter2, class Compared>
bool lexicographical_compare(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, Compared comp) {
    for (; first1 != last1 && first2 != last2; first1++, first2++) {
        if (comp(*first1, *first2)) return true;
        if (comp(*first2, *first1)) return false;
    }
    return first1 == last1 && first2 != last2;
}

// Specific version for const unsigned char*
bool lexicographical_compare(const unsigned char* first1, const unsigned char* last1, const unsigned char* first2, const unsigned char* last2) {
    const auto len1 = last1 - first1;
    const auto len2 = last2 - first2;
    // First compare the element in the same length
    const auto result = std::memcmp(first1, first2, saberstl::min(len1, len2));
    // If the result is the same, return the longer one
    return result != 0 ? result < 0 ? len1 < len2;
}

}


#endif // !SABER_ALGOBASE_H