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



} // saberstl


#endif