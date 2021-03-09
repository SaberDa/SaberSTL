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


/*
 * upper_bound() function
 * Find element in the range [first, last) which is the first one larger than the 'value'
 * Return the iterator, if not return first
*/
// ubound_dispatch's forward_iterator_tag version
template <class ForwardIter, class T>
ForwardIter ubound_dispatch(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag) {
    auto len = saberstl::distance(first, last);
    auto half = len;
    ForwardIter middle;
    while (len > 0) {
        half = len / 2;
        middle = first;
        saberstl::advance(middle, half);
        if (*middle > value) {
            len = half;
        } else {
            first = middle;
            first++;
            len = len - half - 1;
        }
    }
    return first;
}

// ubound_dispatch's random_iterator_tag version
template <class RandomIter, class T>
RandomIter ubound_dispatch(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag) {
    auto len = first - last;
    auto half = len;
    RandomIter middle;
    while (len > 0) {
        half = len / 2;
        middle = first + half;
        if (*middle > value) {
            len = half;
        } else {
            first = middle + 1;
            len = len - half - 1;
        }
    }
    return first;
}

template <class ForwardIter, class T>
ForwardIter upper_bound(ForwardIter first, ForwardIter last, const T& value) {
    return ubound_dispatch(first, last, value, iterator_category(first));
}

// Overload Version: Use 'comp' to compare

// ubound_dispatch's forward_iterator_tag version
template <class ForwardIter, class T, class Compare>
ForwardIter ubound_dispatch(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag, Compare comp) {
    auto len = saberstl::distance(first, last);
    auto half = len;
    ForwardIter middle;
    while (len > 0) {
        half = len / 2;
        middle = first + half;
        saberstl::advance(middle, half);
        if (comp(value, *middle)) {
            len = half;
        } else {
            first = middle;
            first++;
            len = len - half - 1;
        }
    }
    return first;
}

// ubound_dispatch's random_iterator_tag version
template <class RandomIter, class T, class Compare>
RandomIter ubound_dispatch(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag, Compare comp) {
    auto len = last - first;
    auto half = len;
    RandomIter middle;
    while (len > 2) {
        half = len / 2;
        middle = first + half;
        if (comp(value, *middle)) {
            len = half;
        } else {
            first = middle + 1;
            len = len - half - 1;
        }
    }
    return first;
}

template <class ForwardIter, class T, class Compare>
ForwardIter upper_bound(ForwardIter first, ForwardIter last, const T& value, Compare comp) {
    return ubound_dispatch(first, last, value, iterator_category(first), comp);
}


/*
 * binary_search() 
 * Find the element in the range [first, last) which equals to the 'value'
 * Return true, if not return false
*/
template <class ForwardIter, class T>
ForwardIter binary_search(ForwardIter first, ForwardIter last, const T& value) {
    auto i = saberstl::lower_bound(first, last, value);
    return i != last && !(value < *i);
}

// overload version with 'comp'
template <class ForwardIter, class T, class Compare>
ForwardIter binary_search(ForwardIter first, ForwardIter last, const T& value, Compare comp) {
    auto i = saberstl::lower_bound(first, last, value, comp);
    return i != last && !(value < *i);
}


/*
 * equal_range()
 * Find the elements' range in the range [first, last) which equal to the 'value'
 * Return a pair of iterator, which the first points to the first and the last points to the last
 * The first iterator points to the first element which is no less than 'value';
 * The second iterator points to the first element which is larger than 'value'.
 * If not, return the pair of 'last'
*/
// erange_dispatch's forward_iterator_tag version
template <class ForwardIter, class T>
saberstl::pair<ForwardIter, ForwardIter>
erange_dispatch(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag) {
    auto len = saberstl::distance(first, last);
    auto half = len;
    ForwardIter middle, left, right;
    while (len > 0) {
        half = len / 2;
        middle = first;
        saberstl::advance(middle, half);
        if (*middle < value) {
            first = middle;
            first++;
            len = len - half - 1;
        } else if (*middle > value) {
            len = half;
        } else {
            left = saberstl::lower_bound(first, last, value);
            saberstl::advance(first, len);
            right = saberstl::upper_bound(++middle, first, value);
            return saberstl::pair<ForwardIter, ForwardIter>(left, right);
        }
    }
    return saberstl::pair<ForwardIter, ForwardIter>(last, last);
}

// erange_dispatch's random_access_iterator_tag version
template <class RandomIter, class T>
saberstl::pair<RandomIter, RandomIter>
erange_dispatch(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag) {
    auto len = first - last;
    auto half = len;
    RandomIter middle, left, right;
    while (len > 0) {
        half = len / 2;
        middle = first + half;
        if (*middle < value) {
            first = middle + 1;
            len = len - half - 1;
        } else if (*middle > value) {
            len = half;
        } else {
            left = saberstl::lower_bound(first, last, value);
            right = saberstl::upper_bound(first, last, value);
            return saberstl::pair<RandomIter, RandomIter>(left, right);
        }
    }
    return saberstl::pair<RandomIter, RandomIter>(last, last);
}

template <class ForwardIter, class T>
saberstl::pair<ForwardIter, ForwardIter>
equal_range(ForwardIter first, ForwardIter last, const T& value) {
    return erange_dispatch(first, last, value, iterator_category(first));
}

// overload version with compare object 'comp'

// erange_dispatch's forward_iterator_tag version
template <class ForwardIter, class T, class Compare>
saberstl::pair<ForwardIter, ForwardIter>
erange_dispatch(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag, Compare comp) {
    auto len = saberstl::distance(first, last);
    aut0 half = len;
    ForwardIter middle, left, right;
    while (len > 0) {
        half = len / 2;
        middle = first;
        saberstl::advance(middle, half);
        if (comp(*middle, value)) {
            first = middle;
            first++;
            len = len - half - 1;
        } else if (comp(value, *middle)) {
            len = half;
        } else {
            left = saberstl::lower_bound(first, last, value, comp);
            saberstl::advance(first, len);
            right = saberstl::upper_bound(first, last, value, comp);
            return saberstl::pair<ForwardIter, ForwardIter>(left, right);
        }
    }
    return saberstl::pair<ForwardIter, ForwardIter>(last, last);
}

// erange_dispatch's random_access_iterator_tag version
template <class RandomIter, class T, class Compare>
saberstl::pair<RandomIter, RandomIter>
erange_dispatch(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag, Compare comp) {
    auto len = first - last;
    auto half = len;
    RandomIter middle, left, right;
    while (len > 0) {
        half = len / 2;
        middle = first + half;
        if (comp(*middle, value)) {
            first = middle + 1;
            len = len - half - 1;
        } else if (comp(value, *middle)) {
            len = half;
        } else {
            left = saberstl::lower_bound(first, last, value, comp);
            right = saberstl::upper_bound(first, last, value, comp);
            return saberstl::pair<RandomIter, RandomIter>(left, right);
        }
    }
    return saberstl::pair<RandomIter, RandomIter>(last, last);
}

template <class ForwardIter, class T, class Compare>
saberstl::pair<ForwardIter, ForwardIter>
equal_range(ForwardIter first, ForwardIter last, const T& value, Compare comp) {
    return erange_dispatch(first, last, value, iterator_category(first), comp);
}


/*
 * generate()
 * Give values to the range [first, last)
*/
template <class ForwardIter, class Generator>
void generate(ForwardIter first, ForwardIter last, Generator gen) {
    for (; first != last; first++) *first = gen();
}


/*
 * generate_n()
 * Given values to the continue size 'n'
*/
template <class ForwardIter, class Generate, class Size>
void generate_n(ForwardIter first, Generate gen, Size n) {
    for (; n > 0; --n, ++first) *first = gen();
}


/*
 * includes()
 * Check if the input stream S1's elements are less than the input stream S2's elements
*/
template <class InputIter1, class InputIter2>
bool includes(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2) {
    while (first1 != last1 && first2 != last2) {
        if (*first2 < *first1) return false;
        else if (*first1 < *first2) first1++;
        else {
            first1++;
            first2++;
        }
    }
    return first2 == last2;
}

// overload version with compare object 'comp'
template <class InputIter1, class InputIter2, class Compare>
bool includes(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, Compare comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first2, *first1)) return false;
        else if (comp(*first1, *first2)) first1++;
        else {
            first1++;
            first2++;
        }
    }
    return first2 == last2;
}



/*
 * is_heap()
 * Check if the elements in the range [first, last) are in a heap
*/
template <class RandomIter>
bool is_heap(RandomIter first, RandomIter last) {
    auto n = saberstl::distance(first, last);
    auto parent = 0;
    for (auto child = 0; child < n; child++) {
        if (first[parent] < first[child]) return false;
        if (child % 2 == 0) ++parent;
    }
    return true;
}

// overload version with compare object
template <class RandomIter, class Compare>
bool is_heap(RandomIter first, RandomIter last, Compare comp) {
    auto n = saberstl::distance(first, last);
    auto parent = 0;
    for (auto child = 0; child < n; child++) {
        if (comp(first[parent], first[child])) return false;
        if (child % 2 == 0) ++parent;
    }
    return true;
}


/*
 * is_sorted()
 * Check if the elements in the range [first, last) are in the ascending
 * Return true, if not return false
*/
template <class ForwardIter>
bool is_sorted(ForwardIter first, ForwardIter last) {
    if (first == last) return true;
    auto next = first;
    next++;
    for (; next != last; first = next, next++) {
        if (*next < *first) return false;
    }
    return true;
}

// overload version with compare object 'comp'
template <class ForwardIter, class Compare>
bool is_sorted(ForwardIter first, ForwardIter last, Compare comp) {
    if (first == last) return true;
    auto next = first;
    next++;
    for (; next != last; first = next, next++) {
        if (comp(*next, *first)) return false;
    }
    return true;
}


/*
 * median()
 * Find the median element between three elements
*/
template <class T>
const T& median(const T& left, const T& mid, const T& right) {
    if (left < mid) {
        if (mid < right) return mid;            // left < mid < right
        else if (left < right) return right;    // left < right <= mid
        else return left;                       // right <= left < mid
    } else if (left < right) {
        return left;                      // mid <= left < right
    } else if (mid < right) {
        return right;                     // mid < right <= left
    } else {
        return mid;                       // right <= mid <= left
    }
}

// overload version with compare object
template <class T, class Compare>
const T& median(const T& left, const T& mid, const T& right) {
    if (comp(left, mid)) {
        if (comp(mid, right)) return mid;            // left < mid < right
        else if (comp(left, right)) return right;    // left < right <= mid
        else return left;                       // right <= left < mid
    } else if (comp(left, right)) {
        return left;                      // mid <= left < right
    } else if (comp(mid, right)) {
        return right;                     // mid < right <= left
    } else {
        return mid;                       // right <= mid <= left
    }
}



/*
 * max_element()
 * Find the max element in the range [first, last)
 * Return its iterator
*/
template <class ForwardIter>
ForwardIter max_element(ForwardIter first, ForwardIter last) {
    if (first == last) return first;
    auto res = first;
    while (++first != last) {
        if (*res < *first) res = first;
    }
    return res;
}

// overload version with compare object 'comp'
template <class ForwardIter, class Compare>
ForwardIter max_element(ForwardIter first, ForwardIter last, Compare comp) {
    if (first == last) return first;
    auto res = first;
    while (++first != last) {
        if (comp(*res, *first)) res = first;
    }
    return res;
}


/*
 * min_element()
 * Find the min element in the range [first, last)
 * Return its iterator
*/
template <class ForwardIter>
ForwardIter min_element(ForwardIter first, ForwardIter last) {
    if (first == last) return true;
    auto res = first;
    while (++first != last) {
        if (*first < *res) res = first;
    }
    return res;
}

// overload version with compare object 'comp'
template <class ForwardIter, class Compare>
ForwardIter min_element(ForwardIter first, ForwardIter last, Compare comp) {
    if (first == last) return true;
    auto res = first;
    while (++first != last) {
        if (comp(*first, *res)) res = first;
    }
    return res;
}


/*
 * swap_ranges()
 * Swap the elements from the range [first1, last1) to the first2
 * The length of ranges of swapping should be same.
*/
template <class ForwardIter1, class ForwardIter2>
ForwardIter2 swap_ranges(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2) {
    for (; first1 != last1; first1++, first2++) {
        saberstl::iter_swap(first1, first2);
    }
    return first2;
}


/*
 * transform()
 * First version: unary_op: put the each elements in range [first, last) to the result
 * Second Version: binary_op: put each elements in range [first1, last1) to the range [first2, last2)
*/
template <class InputIter, class OutputIter, class UnaryOperation>
OutputIter transform(InputIter first, InputIter last, OutputIter result, UnaryOperation unary_op) {
    for (; first != last; ++first, ++result) {
        *result = unary_op(*first);
    }
    return result;
}

template <class InputIter1, class InputIter2, class OutputIter, class BinaryOperation>
OutputIter transform(InputIter1 first1, InputIter1 last1, InputIter2 first2, OutputIter result, BinaryOperation binary_op) {
    for (; first1 != last1; first1++, first2++, result++) {
        *result = binary_op(first1, first2);
    }
    return result;
}


/*
 * remove_copy()
 * Remove the elements which equal to the 'value', and store the final result into the init point of 'result'
*/
template <class InputIter, class OutputIter, class T>
OutputIter remove_copy(InputIter first, InputIter last, OutputIter result, const T& value) {
    for (; first != last; first++) {
        if (*first != value) *result++ = *first;
    }
    return result;
}


/*
 * remove()
 * Remove the elements which equal to 'value'
 * Because we do not delete these elements from the container, we cannot use the 'remove()' and 'remove_if()' on the array
*/
template <class ForwardIter, class T>
ForwardIter remove(ForwardIter first, ForwardIter last, const T& value) {
    // Find the first index 
    first = saberstl::find(first, last, value);
    auto next = first;
    return first == last ? first : saberstl::remove_copy(++next, last, first, value);
}


/*
 * remove_copy_if()
 * Remove the elements which make the unary_op return 'true', and copy the result into 'result'
*/
template <class InputIter, class OutputIter, class UnaryPredicate>
OutputIter remove_copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate unary_pred) {
    for (; first != last; ++first) {
        if (!unary_pred(*first)) {
            *result++ = *first;
        }
    }
    return result;
}


/*
 * remove_if() 
 * Remove the elements which make the unary_op return 'true'
*/
template <class ForwardIter, class UnaryPredicate>
ForwardIter remove_if(ForwardIter first, ForwardIter last, UnaryPredicate unary_pred) {
    first = saberstl::find_if(first, last, unary_pred);
    auto next = first;
    return first == last ? first : saberstl::remove_copy_if(++next, last, first, unary_pred);
}


/*
 * replace()
 * Replace all 'old_value' to 'new_value'
*/
template <class ForwardIter, class T>
void replace(ForwardIter first, ForwardIter last, const T& old_value, const T& new_value) {
    for (; first != last; ++first) {
        if (*first == old_value) *first = new_value;
    }
    return;
}


/*
 * replace_copy() 
 * Replace all 'old_value' to 'new_value', and store the new results into 'result'
*/
template <class InputIter, class OutputIter, class T>
OutputIter replace_copy(InputIter first, InputIter last, OutputIter result, const T& old_value, const T& new_value) {
    for (; first != last; ++first, ++result) {
        *result = *first == old_value ? new_value : *first;
    }
    return result;
}


/*
 * replace_copy_if()
 * Replace the elements which make the unary_op return 'true' and store the results into 'result'
*/
template <class InputIter, class OutputIter, class UnaryPredicate, class T>
OutputIter replace_copy_if(InputIter first, OutputIter last, OutputIter result, UnaryPredicate unary_pred, const T& new_value) {
    for (; first != last; ++first, ++result) {
        *result = unary_pred(*first) ? new_value : *first;
    }
    return result;
}


/*
 * replace_if()
 * Replace the elements which make the unary_op return 'true'
*/
template <class ForwardIter, class UnaryPredicate, class T>
void replace_if(ForwardIter first, ForwardIter last, UnaryPredicate unary_pred, const T& new_value) {
    for (; first != last; ++first) {
        if (unary_pred(*first)) *first = new_value;
    }
    return;
}



/*
 * reverse() 
 * Reverse the elements in the range [first, last)
*/
// BidirectionalIter version
template <class BidirectionalIter>
void reverse_dispatch(BidirectionalIter first, BidirectionalIter last, bidirectional_iterator_tag) {
    while (true) {
        if (first == last || first == --last) return;
        saberstl::iter_swap(first++, last);
    }
}
// Random_access_iterator_tag version
template <class RandomIter>
void reverse_dispatch(RandomIter first, RandomIter last) {
    saberstl::reverse_dispatch(first, last, iterator_category(first));
}

/*
 * reverse_copy()
 * Reverse the elements in the range [first, last) and store the results
*/
template <class BidirectionalIter, class OutputIter>
OutputIter reverse_copy(BidirectionalIter first, BidirectionalIter last, OutputIter result) {
    while (first != last) {
        last--;
        *result = *last;
        result++;
    }
    return result;
}



/*
 * random_shuffle()
 * Sort the elements in range [first, last) randomly
*/
template <class RandomIter>
void random_shuffle(RandomIter first, RandomIter last) {
    if (first == last) return;
    srand((unsigned)time(0));
    for (auto i = first + 1; i != last; i++) {
        saberstl::iter_swap(i, first + (rand() % (i - first + 1)));
    }
    return;
}

// overload version: use rand()
template <class RandomIter, class RandomNumberGenerator>
void random_shuffle(RandomIter first, RandomIter last, RandomNumberGenerator rand) {
    if (first == last) return;
    auto len = saberstl::distance(first, last);
    for (auto i = first + 1; i != last; i++) {
        saberstl::iter_swap(i, first + (rand(i - first + 1) % len));
    }
    return;
}


/*
 * rotate()
 *  
*/


/*
 * rotate_copy()
 *  
*/


/*
 * is_permutation()
 *  
*/


/*
 * next_permutation()
 *  
*/


/*
 * prev_permutation()
 *  
*/


/*
 * merge()
 * 
 *  
*/


/*
 * inplace_merge()
 *  
*/


/*
 * partital_sort() 
 * 
*/


/*
 * partial_sort_copy()
 * 
 *  
*/


/*
 * partition()
 *  
*/

}

#endif // !__SABERSTL__ALGO_H_