#pragma once
#include "types.h"

// https://man7.org/linux/man-pages/man2/syscall.2.html#DESCRIPTION

__attribute__((always_inline))
static inline uint64_t syscall0(uint64_t const syscallNumber)
{
    uint64_t ret = 0;

    asm volatile
    (
        "syscall"
        : "=a"(ret) // rax
        : "a"(syscallNumber)
        : "rcx", "r11", "memory"
    );

    return ret;
}

__attribute__((always_inline))
static inline uint64_t syscall1(uint64_t const syscallNumber, uint64_t const arg1)
{
    uint64_t ret = 0;

    asm volatile
    (
        "syscall"
        : "=a"(ret) // rax
        : "a"(syscallNumber), "D"(arg1)
        : "rcx", "r11", "memory"
    );

    return ret;
}

__attribute__((always_inline))
static inline uint64_t syscall2(uint64_t const syscallNumber, uint64_t const arg1, uint64_t const arg2)
{
    uint64_t ret = 0;

    asm volatile
    (
        "syscall"
        : "=a"(ret) // rax
        : "a"(syscallNumber), "D"(arg1), "S"(arg2)
        : "rcx", "r11", "memory"
    );

    return ret;
}

__attribute__((always_inline))
static inline uint64_t syscall3(uint64_t const syscallNumber, uint64_t const arg1, uint64_t const arg2, uint64_t const arg3)
{
    uint64_t ret = 0;

    asm volatile
    (
        "syscall"
        : "=a"(ret) // rax
        : "a"(syscallNumber), "D"(arg1), "S"(arg2), "d"(arg3)
        : "rcx", "r11", "memory"
    );

    return ret;
}

__attribute__((always_inline))
static inline uint64_t syscall4(uint64_t const syscallNumber, uint64_t const arg1, uint64_t const arg2, uint64_t const arg3, uint64_t const arg4)
{
    uint64_t ret = 0;

    register uint64_t r10 asm("r10") = arg4;

    asm volatile
    (
        "syscall"
        : "=a"(ret) // rax
        : "a"(syscallNumber), "D"(arg1), "S"(arg2), "d"(arg3), "r"(r10)
        : "rcx", "r11", "memory"
    );

    return ret;
}

__attribute__((always_inline))
static inline uint64_t syscall5(uint64_t const syscallNumber, uint64_t const arg1, uint64_t const arg2, uint64_t const arg3, uint64_t const arg4, uint64_t const arg5)
{
    uint64_t ret = 0;

    register uint64_t r10 asm("r10") = arg4;
    register uint64_t r8 asm("r8") = arg5;

    asm volatile
    (
        "syscall"
        : "=a"(ret) // rax
        : "a"(syscallNumber), "D"(arg1), "S"(arg2), "d"(arg3), "r"(r10), "r"(r8)
        : "rcx", "r11", "memory"
    );

    return ret;
}

__attribute__((always_inline))
static inline uint64_t syscall6(uint64_t const syscallNumber, uint64_t const arg1, uint64_t const arg2, uint64_t const arg3, uint64_t const arg4, uint64_t const arg5, uint64_t const arg6)
{
    uint64_t ret = 0;

    register uint64_t r10 asm("r10") = arg4;
    register uint64_t r8 asm("r8") = arg5;
    register uint64_t r9 asm("r9") = arg6;

    asm volatile
    (
        "syscall"
        : "=a"(ret) // rax
        : "a"(syscallNumber), "D"(arg1), "S"(arg2), "d"(arg3), "r"(r10), "r"(r8), "r"(r9)
        : "rcx", "r11", "memory"
    );

    return ret;
}