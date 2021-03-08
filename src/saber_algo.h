#ifndef __SABERSTL__ALGO_H_
#define __SABERSTL__ALGO_H_

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4244)
#endif

#include <cstddef>
#include <ctime>

#include "saber_algobase.h"
#include "saber_memory.h"
#include "saber_heap_algo.h"
#include "saber_functional.h"

namespace saberstl {

/*
 * all_of
 * Check if all elements in range [first, last) satisfies unary operation 'unary_pred' are 'true'
 * If they are, return true
*/
template <class InputIter, class UnaryPredicate>
bool all_of(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    for (; first != last; first++) {
        if (!unary_pred(*first)) return false;
    }
    return true;
}

/*
 * any_of
 * Check if there is one element in range [first, last) satisfies unary operation 'unary_pred' is true
 * If there is, return true
*/
template <class InputIter, class UnaryPredicate>
bool any_of(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    for (; first != last; first++) {
        if (unary_pred(*first)) return true;
    }
    return false;
}

/*
 * none_of
 * Check if all the elements in range [first, last) are not satisfy unary operation 'unary_pred' are false
 * If they are, return true
*/
template <class InputIter, class UnaryPredicate>
bool noneof(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    for (; first != last; first++) {
        if (unary_pred(*first)) return false;
    }
    return true;
}

/*
 * count
 * Compare the elements' value which in range [first, last) with the given value. Default use 'operator=='
 * Return the number of equal elements
*/
template <class InputIter, class T> 
size_t count(InputIter first, InputIter last, const T& value) {
    size_t n = 0;
    for (; first != last; first++) {
        if (*first == value) n++;
    }
    return n;
}

/*
 * count_if
 * Do unary operation for all the elements in range [first, last).
 * Return the number of elements which result is true
*/
template <class InputIter, class UnaryPredicate>
size_t count_if(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    size_t n = 0;
    for (; first != last; first++) {
        if (unary_pred(*first)) n++;
    }
    return n;
}

/*
 * find
 * Find the elements in range [first, last) which value equals to the given value
 * return the iterator which points to the result element
*/
template <class InputIter, class T> 
InputIter find(InputIter first, InputIter last, const T& value) {
    while(first != last && *first != value) first++;
    return first;
}

/*
 * find_if
 * Find the first element in range [first, last) which satisfies the unary operation 'unary_pred' is true
 * return the iterator which points to this element
*/
template <class InputIter, class UnaryPredicate>
InputIter find_if(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    while (first != last && !unary_pred(*first)) first++;
    return first;
}

/*
 * find_if_not
 * Find the first element in range [first, last) which satisfies the unary operation 'unary_pred' is false
 * return the iterator which points to this element
*/ 
template <class InputIter, class UnaryPredicate>
InputIter find_if_not(InputIter first, InputIter last, UnaryPredicate unary_pred) {
    while (first != last && unary_pred(*first)) first++;
    return first;
}

/*
 * search
 * Find the range [first2, last2) first appear point in range [first1, last1)
*/
template <class ForwardIter1, class ForwardIter2>
ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2) {
    auto d1 = saberstl::distance(first1, last1);
    auto d2 = saberstl::distance(first2, last2);
    if (d1 < d2) return last1;
    auto current1 = first1;
    auto current2 = first2;
    while (current2 != last2) {
        if (*current1 == *current2) {
            current1++;
            current2++;
        } else {
            if (d1 == d2) return last1;
            else {
                current1 = ++first1;
                current2 = first2;
                --d1;
            }
        }
    }
    return first1;
}

// Overload version, use the 'comp' as the compare function
template <class ForwardIter1, class ForwardIter2, class Compared>
ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, Compared comp) {
    auto d1 = saberstl::distance(first1, last1);
    auto d2 = saberstl::distance(first2, last2);
    if (d1 < d2) return last1;
    auto current1 = first1;
    auto current2 = first2;
    while (current2 != last2) {
        if (comp(*current1, *current2)) {
            current1++;
            current2++;
        } else {
            if (d1 == d2) return last1;
            else {
                current1 = ++ first1;
                current2 = first2;
                d1--;
            }
        }
    }
    return first1;
}

/*
 * search_n
 * Find the subsequence which components with n 'value' in the range [first, last)
 * return the iterator which points to the begin of the subsequence
*/
template <class ForwardIter, class Size, class T>
ForwardIter search_n(ForwardIter first, ForwardIter last, Size n, const T& value) {
    if (n <= 0) return first;
    first == saberstl::find(first, last, value);
    while (first != last) {
        auto m = n - 1;
        auto i = first;
        i++;
        while (i != last && m != 0 && *i == value) {
            i++;
            m--;
        }
        if (m == 0) return first;
        else first = saberstl::find(i, last, value);
    }
    return last;
}

// Overload version, use the 'comp' as the compare function
template <class ForwardIter, class Size, class T, class Compared>
ForwardIter search_n(ForwardIter first, ForwardIter last, Size n, const T& value, Compared comp) {
    if (n <= 0) return first;
    while (first != last) {
        if (comp(*first, value)) break;
        first++;
    }
    while (first != last) {
        auto m = n - 1;
        auto i = first;
        i++;
        while (i != last && m != 0 && comp(*i, value)) {
            i++;
            m--;
        }
        if (m == 0) return first;
        else {
            while (i != last) {
                if (comp(*i, value)) break;
                i++;
            }
            first = i;
        }
    }
    return last;
}

/*
 * find_end
 * Search the range [first2, last2) the last appear point in range [first1, last1)
 * If there is no point, return last1
*/
// find_end_dispatch's forward_iterator_tag version
template <class ForwardIter1, class ForwardIter2>
ForwardIter1 find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1, 
                               ForwardIter2 first2, ForwardIter2 last2, 
                               forward_iterator_tag, forward_iterator_tag) {
    if (first2 == last2) return last1;
    auto result = last1;
    while (true) {
        auto new_result = saberstl::find(first1, last1, first2, last2);
        if (new_result == last1) return result;
        else {
            result = new_result;
            first1 = new_result;
            first1++;
        }
    }
}

// find_end_dispatch's bidirectional_iterator_tag version
template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter1
find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1, 
                  BidirectionalIter2 first2, BidirectionalIter2 last2,
                  bidirectional_iterator_tag, bidirectional_iterator_tag) {
    typedef reverse_iterator<BidirectionalIter1> reviter1;
    typedef reverse_iterator<BidirectionalIter2> reviter2;
    reviter1 rlast1(first1);
    reviter2 rlast2(first2);
    reviter1 rresult = saberstl::search(reviter1(last1), rlast1, reviter2(last2), rlast2);
    if (rresult == rlast1) return last1;
    auto result = rresult.base();
    saberstl::advance(result, -saberstl::distance(first2, last2));
    return result;
}

template <class ForwardIter1, class ForwardIter2>
ForwardIter1
find_end(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2) {
    typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
    typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
    return saberstl::find_end_dispatch(first1, last1, fist2, last2, Category1(), Category2());
}

// Overload version, use the 'comp' as the compare function

// find_end_dispatch's forward_iterator_tag version
template <class ForwardIter1, class ForwardIter2, class Compared>
ForwardIter1 find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1, 
                               ForwardIter2 first2, ForwardIter2 last2, 
                               forward_iterator_tag, forward_iterator_tag, Compared comp) {
    if (first2 == last2) return last1;
    auto result = last1;
    while (true) {
        auto new_result = saberstl::find(first1, last1, first2, last2, comp);
        if (new_result == last1) return result;
        else {
            result = new_result;
            first1 = new_result;
            first1++;
        }
    }
}

// find_end_dispatch's bidirectional_iterator_tag version
template <class BidirectionalIter1, class BidirectionalIter2, class Compared>
BidirectionalIter1
find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1, 
                  BidirectionalIter2 first2, BidirectionalIter2 last2,
                  bidirectional_iterator_tag, bidirectional_iterator_tag, Compared comp) {
    typedef reverse_iterator<BidirectionalIter1> reviter1;
    typedef reverse_iterator<BidirectionalIter2> reviter2;
    reviter1 rlast1(first1);
    reviter2 rlast2(first2);
    reviter1 rresult = saberstl::search(reviter1(last1), rlast1, reviter2(last2), rlast2, comp);
    if (rresult == rlast1) return last1;
    auto result = rresult.base();
    saberstl::advance(result, -saberstl::distance(first2, last2));
    return result;
}

template <class ForwardIter1, class ForwardIter2, class Compared>
ForwardIter1
find_end(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, Compared comp) {
    typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
    typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
    return saberstl::find_end_dispatch(first1, last1, fist2, last2, Category1(), Category2(), comp);
}

/*
 * find_first_of
 * Find elements which in [first2, last2) in range [first1, last1)
 * return the iterator which points to the first appear point
*/
template <class InputIter, class ForwardIter>
InputIter find_first_of(InputIter first1, InputIter last1, ForwardIter first2, ForwardIter last2) {
    for (; first1 != last1; first1++) {
        for (auto iter = first2; iter != last2; iter++) {
            if (*first1 == *iter) return first1;
        }
    }
    return last1;
}

// Overload version, use the 'comp' as the compare function
template <class InputIter, class ForwardIter, class Compared>
InputIter find_first_of(InputIter first1, InputIter last1, ForwardIter first2, ForwardIter last2, Compared comp) {
    for (; first1 != last1; first1++) {
        for (auto iter = first2; iter != last2; iter++) {
            if (comp(*first1, *iter)) return first1;
        }
    }
    return last1;
}

/*
 * for_each
 * Using a function object 'f' to do operation for every elements in range [first, last) without changing their value
 * 'f' can return a value, but usually ignore it
*/
template <class InputIter, class Function>
Function for_each(InputIter first, InputIter last, Function f) {
    for (; first != last; first++) {
        f(*first);
    }
    return f;
}

/*
 * adjacent_find
 * Find the first pair of matching adjacent elements, default using operator==.
 * If there exists a pair, return a iterator which points to the first element
*/
template <class ForwardIter>
ForwardIter adjacent_find(ForwardIter first, ForwardIter last) {
    if (first == last) return last;
    auto next = first;
    while (++next != last) {
        if (*next == *first) return first;
        first = next;
    }
    return last;
}

// Overload version, use the 'comp' as the compare function
template <class ForwardIter, class Compared> 
ForwardIter adjacent_find(ForwardIter first, ForwardIter last, Compared comp) {
    if (first == last) return last;
    auto next = first;
    while (++next != last) {
        if (comp(*first, *next)) return first;
        first = next;
    }
    return last;
}

/*
 * lower_bound
 * Find the element in the range [first, last) which is no less than the 'value'
 * Return its iterator, if not return 'last'
*/
// lbound_dispatch's forward_iterator_tag version
template <class ForwardIter, class T>
ForwardIter lbound_dispatch(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag) {
    auto len = saberstl::distance(first, last);
    auto half = len;
    ForwardIter middle;
    while (len > 0) {
        half = len / 2;
        middle = first;
        saberstl::advance(middle, half);
        if (*middle < value) {
            first = middle + 1;
            len = len - half - 1;
        } else {
            len = half;
        }
    }
    return first;
}

// lbound_dispatch's random_access_iterator_tag version
template <class RandomIter, class T>
RandomIter lbound_dispatch(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag) {
    auto len = last - first;
    auto half = len;
    RandomIter middle;
    while (len > 0) {
        half = len / 2;
        middle = first + half;
        if (*middle < value) {
            first = middle + 1;
            len = len - half - 1;
        } else {
            len = half;
        }
    }
    return first;
}

template <class ForwardIter, class T>
ForwardIter lower_bound(ForwardIter first, ForwardIter last, const T& value) {
    return saberstl::lbound_dispatch(first, last, value, iterator_category(first));
}

// Overload Version: Use 'comp' to compare

// lbound_dispatch's forward_iterator_tag version
template <class ForwardIter, class T, class Compare>
ForwardIter lbound_dispatch(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag, Compare comp) {
    auto len = saberstl::distance(first, last);
    auto half = len;
    ForwardIter middle;
    while (len > 0) {
        half = len / 2;
        middle = first;
        saberstl::advance(middle, half);
        if (comp(*middle, value)) {
            first = middle + 1;
            len = len - half - 1;
        } else {
            len = half;
        }
    }
    return first;
}

// lbound_dispatch's random_access_iterator_tag version
template <class RandomIter, class T, class Compare>
RandomIter lbound_dispatch(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag, Compare comp) {
    auto len = last - first;
    auto half = len;
    RandomIter middle;
    while (len > 0) {
        half = len / 2;
        middle = first + half;
        if (comp(*middle, value)) {
            first = middle + 1;
            len = len - half - 1;
        } else {
            len = half;
        }
    }
    return first;
}

template <class ForwardIter, class T, class Compare>
ForwardIter lower_bound(ForwardIter first, ForwardIter last, const T& value, Compare comp) {
    return lbound_dispatch(first, last, value, iterator_category(first), comp);
}

}

#endif // !__SABERSTL__ALGO_H_