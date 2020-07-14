#ifndef __SABER_TYPE_H__
#define __SABER_TYPE_H__

/* Use standard header for type */ 
#include <type_traits>

namespace saberstl {

/* ==================== Helper Struct ==================== */
template <class T, T v>
struct s_integral_constant {
    static constexpr T value = v;
};

template <bool b> 
using s_bool_constant = s_integral_constant<bool, b>;

typedef s_bool_constant<true> s_true_type;
typedef s_bool_constant<false> s_false_type;

/* ==================== Type Traits ==================== */

/* is_pair */

// --- forward delcaration begin
template <class T1, class T2>
struct pair;
// --- forward delcaration end

template <class T>
struct is_pair : saberstl::s_false_type {};

template <class T1, class T2>
struct is_pair<saberstl::pair<T1, T2>> : saberstl::s_true_type {};

} // namespace saberstl

#endif // __SABER_TYPE_H__