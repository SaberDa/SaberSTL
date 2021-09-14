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
}; // struct char_traits

// Partialized char_traits<char>
template <>
struct char_traits<char> {

    typedef char char_type;

    static size_t length(const char_type* str) noexcept {
        return std::strlen(str);
    }

    static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept {
        return std::memcmp(s1, s2, n);
    }

    static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept {
        SABERSTL_DEBUG(src + n <= dst || dst + n <= src);
        return static_cast<char_type*>(std::memcpy(dst, src, n));
    }

    static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept {
        return static_cast<char_type*>(std::memmove(dst, src, n));
    }

    static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept {
        return static_cast<char_type*>(std::memset(dst, ch, count));
    }
    
}; // struct char_traits<char>

// Partialized char_traits<wchar_t>
template <>
struct char_traits<wchar_t> {
    
    typedef wchar_t char_type;

    static size_t length(const char_type* str) noexcept {
        return std::wcslen(str);
    }

    static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept {
        return std::wmemcmp(s1, s2, n);
    }

    static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept {
        SABERSTL_DEBUG(src + n <= dst || dst + n <= src);
        return static_cast<char_type*>(std::wmemcpy(dst, src, n));
    }

    static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept {
        return static_cast<char_type*>(std::wmemmove(dst, src, n));
    }

    static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept {
        return static_cast<char_type*>(std::wmemset(dst, ch, count));
    }

}; // struct char_traits<wchar_t>

// Partialized char_traits<char16_t>
template <>
struct char_traits<char16_t> {

    typedef char16_t char_type;

        static size_t length(const char_type* str) noexcept {
        size_t len = 0;
        for (; *str != char_type(0); str++) len++;
        return len;
    }

    static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept {
        for (; n != 0; n--, s1++, s2++) {
            if (*s1 < *s2) return -1;
            if (*s1 > *s2) return 1;
        }
        return 0;
    }

    static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept {
        SABERSTL_DEBUG(src + n <= dst || dst + n <= src);
        char_type* r = dst;
        for (; n != 0; n--, dst++, src++) {
            *dst = *src;
        }
        return r;
    }

    static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept {
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

    static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept {
        char_type* r = dst;
        for (; count > 0; count--, dst++) 
            *dst = ch;
        return r;
    }

}; // struct char_traits<char16_t> 

} // namespace saberstl

#endif // SABERSTL_BASIC_STRING_H