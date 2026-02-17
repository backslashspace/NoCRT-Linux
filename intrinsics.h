#pragma once
#include "types.h"

// ░░░ Constants ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░



// ░░░ x86 Other ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░



// ░░░ x86 RNG ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

// https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=rdrand&ig_expand=5267
static inline boolean_t RdRand16X86(uint16_t* val)
{
    boolean_t flag;
    asm
    (
        "rdrand %0;"
        "setc %1;"
        : "=r"(*val), "=r"(flag)
        :
        : "cc"
    );
    return flag;
}

static inline boolean_t RdRand32X86(uint32_t* val)
{
    boolean_t flag;
    asm
    (
        "rdrand %0;"
        "setc %1;"
        : "=r"(*val), "=r"(flag)
        :
        : "cc"
    );
    return flag;
}

static inline boolean_t RdRand64X86(uint64_t* val)
{
    boolean_t flag;
    asm
    (
        "rdrand %0;"
        "setc %1;"
        : "=r"(*val), "=r"(flag)
        :
        : "cc"
    );
    return flag;
}

// https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=rdseed&ig_expand=5267
static inline boolean_t RdSeed16X86(uint16_t* val)
{
    boolean_t flag;
    asm volatile
    (
        "rdseed %0;"
        "setc %1;"
        : "=r"(*val), "=r"(flag)
        :
        : "cc"
    );
    return flag;
}

static inline boolean_t RdSeed32X86(uint32_t* val)
{
    boolean_t flag;
    asm volatile
    (
        "rdseed %0;"
        "setc %1;"
        : "=r"(*val), "=r"(flag)
        :
        : "cc"
    );
    return flag;
}

static inline boolean_t RdSeed64X86(uint64_t* val)
{
    boolean_t flag;
    asm volatile
    (
        "rdseed %0;"
        "setc %1;"
        : "=r"(*val), "=r"(flag)
        :
        : "cc"
    );
    return flag;
}

// ░░░ x86 String ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

// use when destination < source
__attribute__((always_inline))
static inline void MemoryCopyX86(void* destination, const void* source, uint64_t count)
{
    asm volatile
    (
        "rep movsb"
        : "+D" (destination), "+S" (source), "+c" (count)
        :
        : "memory"
    );
}

// use when destination > source
__attribute__((always_inline))
static inline void MemoryInverseCopyX86(void* destination, const void* source, uint64_t count)
{
    asm volatile
    (
        "std;"
        "lea rsi, [rsi + rcx * 1 - 1];"
        "lea rdi, [rdi + rcx * 1 - 1];"
        "rep movsb;"
        "cld;"
        : "+D" (destination), "+S" (source), "+c" (count)
        :
        : "memory"
    );
}

__attribute__((always_inline))
static inline void MemoryFillX86(void* destination, uint8_t value, uint64_t count)
{
    asm volatile
    (
        "rep stosb"
        : "+D"(destination), "+c"(count)
        : "a"(value)
        : "memory"
    );
}

__attribute__((always_inline))
static inline boolean_t MemoryCompareX86(const void* buffer, const void* compare, uint64_t count)
{
    boolean_t flag;
    asm volatile
    (
        "repe cmpsb;"
        "setz %0"
        : "=r"(flag), "+S"(compare), "+D"(buffer), "+c"(count)
        :
        : "memory", "cc"
    );
    return flag;
}

__attribute__((always_inline))
static inline boolean_t MemoryIsValueX86(const void* buffer, unsigned char value, uint64_t count)
{
    boolean_t flag;
    asm volatile
    (
        "repe scasb;"
        "setz %0;"
        : "=r"(flag), "+D"(buffer), "+c"(count)
        : "a"(value)
        : "memory", "cc"
    );
    return flag;
}

__attribute__((always_inline))
// returns -1 if no mismatch is found, otherwise the index
static inline int64_t MemoryGetFirstMismatchIndexX86(const void* buffer, const void* compare, uint64_t count)
{
    int64_t intermediate = (int64_t)count;

    asm volatile
    (
        "repe cmpsb;"
        "dec %[count];"
        "sub %[intermediate], 2;"
        "sub %[intermediate], %[count];"
        "cmp %[count], -1;"
        "cmove %[intermediate], %[OK];"
        : "+S"(compare), "+D"(buffer), [count]"+c"(count), [intermediate]"+r"(intermediate)
        : [OK] "r"(-1l)
        : "memory", "cc"
    );

    return intermediate;
}

__attribute__((always_inline))
// returns -1 if no match is found, otherwise the index
static inline int64_t MemoryGetFirstMatchIndexX86(const void* buffer, uint8_t value, uint64_t count)
{
    int64_t intermediate = (int64_t)count;

    asm volatile
    (
        "repne scasb;"
        "dec %[count];"
        "sub %[intermediate], 2;"
        "sub %[intermediate], %[count];"
        "cmp %[count], -1;"
        "cmove %[intermediate], %[OK];"
        : "+D"(buffer), [count]"+c"(count), [intermediate]"+r"(intermediate)
        : "a"(value), [OK] "r"(-1l)
        : "memory", "cc"
    );

    return intermediate;
}

// ░░░ GCC Builtins ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

// https://gcc.gnu.org/onlinedocs/gcc/Stack-Allocation.html
void* __builtin_alloca(uint64_t size);
void* __builtin_alloca_with_align(uint64_t size, uint64_t alignment);