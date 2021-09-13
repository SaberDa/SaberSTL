#ifndef SABERSTL_BASIC_STRING_H
#define SABERSTL_BASIC_STRING_H

// Template Class: basic_string

#include <iostream>

#include "saber_iterator.h"
#include "saber_memory.h"
#include "saber_functional.h"
#include "saber_execptdef.h"

namespace saberstl {

// char_traits

template <class CharType>
struct char_traits {
    typedef CharType char_type;

    static size_t length(const char_type* str) {
        size_t len = 0;
        for (; *str != char_type(0); str++) len++;
        return len;
    }

    static int compare(const char_type* s1, const char_type* s2, size_t n) {
        for (; n != 0; n--, s1++, s2++) {
            if (*s1 < *s2) return -1;
            if (*s1 > *s2) return 1;
        }
        return 0;
    }

    static char_type* copy(char_type* dst, const char_type* src, size_t n) {
        SABERSTL_DEBUG(src + n <= dst || dst + n <= src);
        char_type* r = dst;
        for (; n != 0; n--, dst++, src++) {
            *dst = *src;
        }
        return r;
    }

    static char_type* move(char_type* dst, const char_type* src, size_t n) {
        char_type* r = dst;
        if (dst < src) {
            for (; n != 0; n--, dst++, src++) 
                *dst = *src;
        } else if (src < dst) {
            dst += n;
            src += n;
            for (; n != 0; n--) 
                *--dst = *--src;
        }
        return r;
    }

    static char_type* fill(char_type* dst, char_type ch, size_t count) {
        char_type* r = dst;
        for (; count > 0; count--, dst++) 
            *dst = ch;
        return r;
    }
};

} // namespace saberstl

#endif // SABERSTL_BASIC_STRING_H