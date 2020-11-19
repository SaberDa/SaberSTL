#ifndef __SABERSTL__FUNCTIONAL_H_
#define __SABERSTL__FUNCTIONAL_H_

#include <cstddef>

namespace saberstl {

template <class Arg, class Result>
struct unarg_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

template <class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};


} // namespace saberstl

#endif // !__SABERSTL__FUNCTIONAL_H_