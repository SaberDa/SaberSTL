#ifndef __SABER_ALLOC_H__
#define __SABER_ALLOC_H__

/*
 * This header file contains a class alloc for allocating 
 * and reclaiming memory, implemented as a memory pool
*/

#include <new>
#include <cstddef>
#include <cstdio>

namespace saberstl {

/*
 * Common part: Freelist
 * Use linked list to manage memory fragments, alloc and recover the 
 * memory block which is <= 4k
*/ 
union Freelist {
    union Freelist *next;   // point to next part block
    char data[1];           // store the first address of the current memory part
};

/*
 * Different memory range 
*/ 
enum {
    EAlign128 = 8,
    EAlign256 = 16,
    EAlign512 = 32,
    EAlign1024 = 64,
    EAlign2048 = 128,
    EAlign4096 = 256
};

/* Memory size for small object */
enum { ESmallObjectBytes = 4096 };

/* Number of free lists */
enum { EFreeListsNumber = 56 };


/*
 * class alloc: to alloc the memory
 * If the current memory part is larger than 4096 bytes, call 
 * std::malloc & std::free directly;
 * If the current memory is small, use memory pool to manage them. Each 
 * time alloc a large part of memory and maintain the freelist it owns.
*/
class alloc {
private:
    static char *start_free;        // Start point of memory pool
    static char *end_free;          // End point of memory pool
    static size_t heap_size;        // The addent space for applying heap

    static Freelist *free_list[EFreeListsNumber];   // Store the freelist

public:
    static void *allocate(size_t n);
    static void deallocate(void *p, size_t n);
    static void *reallocate(void *p, size_t old_size, size_t new_size);

private:
    static size_t S_align(size_t bytes);
    static size_t S_round_up(size_t bytes);
    static size_t S_freelist_index(size_t bytes);
    static void *S_refill(size_t n);
    static char *S_chunk_alloc(size_t size, size_t& nobj);
};

/* Initial static variables */

char* alloc::start_free = nullptr;
char* alloc::end_free = nullptr;
size_t alloc::heap_size = 0;

Freelist* alloc::free_list[EFreeListsNumber] = {
    nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
    nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
    nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
    nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
    nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
    nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
    nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr
};

/* Alloc space of size n, n > 0 */
inline void* alloc::allocate(size_t n) {
    Freelist *my_free_list;
    Freelist *result;
    if (n > static_cast<size_t>(ESmallObjectBytes)) return std::malloc(n);
    my_free_list = free_list[S_freelist_index(n)];
    result = my_free_list;
    if (result == nullptr) {
        void *r = S_refill(S_round_up(n));
        return r;
    }
    my_free_list = result->next;
    return result;
}

/* Free p points to the space of size n, p cannot be 0 */
inline void alloc::deallocate(void *p, size_t n) {
    if (n > static_cast<size_t>(ESmallObjectBytes)) {
        std::free(p);
        return;
    }
    Freelist *q = reinterpret_cast<Freelist*>(p);
    Freelist *my_free_list;
    my_free_list = free_list[S_freelist_index(n)];
    q->next = my_free_list;
    my_free_list = q;
}

/*
 * Realloc the space.
 * The function receives three parameters:
 * p: pointer points to new space
 * old_size: origin space size
 * new_size: new space size
*/
inline void* alloc::reallocate(void *p, size_t old_size, size_t new_size) {
    deallocate(p, old_size);
    p = allocate(new_size);
    return p;
}

/* bytes correspond to the increase in size */
inline size_t alloc::S_align(size_t bytes) {
    if (bytes <= 512) {
        return bytes <= 256 
        ? bytes <= 128 ? EAlign128 : EAlign256 
        : EAlign512;
    }
    return bytes <= 2048
    ? bytes <= 1024 ? EAlign1024 : EAlign2048
    : EAlign4096;
}

/* Increase the bytes to the corresponding interval size */
inline size_t alloc::S_round_up(size_t bytes) {
    return ((bytes + S_align(bytes) - 1) & ~(S_align(bytes) - 1));
}

/* According the size of chain, choose the nth free lists */
inline size_t alloc::S_freelist_index(size_t bytes) {
    if (bytes <= 512) {
        return bytes <= 256
        ? bytes <= 128
            ? ((bytes + EAlign128 - 1) / EAlign128 - 1)
            : (15 + (bytes + EAlign256 - 129) / EAlign256) 
        : (23 + (bytes + EAlign512 - 257) / EAlign512);
    }
    return bytes <= 2048
    ? bytes <= 1024
        ? (31 + (bytes + EAlign1024 - 513) / EAlign1024)
        : (39 + (bytes + EAlign2048 - 1025) / EAlign2048)
    : (47 + (bytes + EAlign4096 - 2049) / EAlign4096);
}

/* Refill the free list */
void* alloc::S_refill(size_t n) {
    size_t nblock = 10;
    char *c = S_chunk_alloc(n, nblock);
    Freelist *my_free_list;
    Freelist *result, *cur, *next;
    /*
     * If there is only one block,
     * then return this block to the caller,
     * there is no new node increasing in the free list
    */
    if (nblock == 1) return c;
    /*
     * Else return one block to the caller,
     * and add the rest into free list as the new nodes
    */
    my_free_list = free_list[S_freelist_index(n)];
    result = (Freelist*)c;
    my_free_list = next = (Freelist*)(c + n);
    for (size_t i = 1; ; i++) {
        cur = next;
        next = (Freelist*)((char*)next + n);
        if (nblock - 1 == i) {
            cur->next = nullptr;
            break;
        } else {
            cur->next = next;
        }
    }
    return result;
}

} // saberstl


#endif