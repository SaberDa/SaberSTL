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

// Partialized char_traits<char32_t>
template <>
struct char_traits<char32_t> {

    typedef char32_t char_type;

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

}; // struct char_traits<char32_t> 

// Initialize the minimize buffer size of the basic_string 
#define STRING_INTI_SIZE 32

// template class basic_string
// Parameter 1 represents the type of string;
// Parameter 2 represents the solution of extraction type of string, default using saberstl::char_traits
template <class CharType, class CharTraits = saberstl::char_traits<CharType>>
class basic_string {
public:
    typedef CharTraits                                  traits_type;
    typedef CharTraits                                  char_traits;

    typedef saberstl::allocator<CharType>               allocator_type;
    typedef saberstl::allocator<CharType>               data_allocator;

    typedef typename allocator_type::value_type         value_type;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::difference_type    difference_type;

    typedef value_type*                                 iterator;
    typedef const value_type*                           const_iterator;
    typedef saberstl::reverse_iterator<iterator>        reverse_iterator;
    typedef saberstl::reverse_iterator<const_iterator>  const_reverser_iterator;

    allocator_type get_allocator() {
        return allocator_type();
    }

    static_assert(std::is_pod<CharType>::value, 
                  "Character type of basic_string must be a POD");
    static_assert(std::is_same<CharType, typename traits_type::char_type>::value,
                  "Character must be same as traits_type::char_type");

public:
    // Handle the last point value, ex:
    // if (str.find('a') != string::npos) { /* do something */ }
    static constexpr size_type npos = static_cast<size_type>(-1);

private:
    iterator buffer_;   // Store the initial address of string
    size_type size_;    // Store the size of string
    size_type cap_;     // Store the capacity of string

public:
    
    basic_string() noexcept {
        try_init();
    }

    basic_string(size_type n, value_type ch) : buffer_(nullptr), size_(0), cap_(0) {
        fill_init();
    }

    basic_string(const basic_string& other, size_type pos)
    : buffer_(nullptr), size_(0), cap_(0) {
        init_from(other.buffer_, pos, other.size_ - pos);
    }
    basic_string(const basic_string& other, size_type pos, size_type count) 
    : buffer_(nullptr), size_(0), cap_(0) {
        init_from(other.buffer_, pos, count);
    }

    basic_string(const_pointer str) : buffer_(nullptr), size_(0), cap_(0) {
        init_from(str, 0, char_traits::length(str));
    }
    basic_string(const_pointer str, size_type count) 
    : buffer_(nullptr), size_(0), cap_(0) {
        init_from(str, 0, count);
    }

    template <class Iter, typename std::enable_if<
      saberstl::is_input_iterator<Iter>::value, int>::type = 0>
    basic_string(Iter first, Iter last) {
        copy_init(first, last, iterator_category(first));
    }

    basic_string(const basic_string& rhs) 
    :buffer_(nullptr), size_(0), cap_(0) {
        init_from(rhs.buffer_, 0, rhs.size_);
    }
        
    basic_string(basic_string && rhs) noexcept
    : buffer_(rhs.buffer_), size_(rhs.size_), cap_(rhs.cap_) {
        rhs.buffer_ = nullptr;
        rhs.size_ = 0;
        rhs.cap_ = 0;
    }

    basic_string& operator=(const basic_string& rhs);
    basic_string& operator=(basic_string&& rhs) noexcept;

    basic_string& operator=(const_pointer str);
    basic_string& operator=(value_type ch);

    ~basic_string() {
        destory_buffer();
    }

};

} // namespace saberstl

#endif // SABERSTL_BASIC_STRING_H