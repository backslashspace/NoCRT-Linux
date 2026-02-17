#pragma once
#include "syscalls.h"

// https://x64.syscall.sh/
// https://filippo.io/linux-syscall-table/

// ░░░ Constants ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

#define PROT_NONE 0x0
#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define PROT_EXEC 0x4

#define MAP_ANONYMOUS 0x20
#define MAP_PRIVATE 0x02

#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1
#define CLOCK_BOOTTIME 7
#define CLOCK_MONOTONIC_RAW 4
#define CLOCK_PROCESS_CPUTIME_ID 2

#define TIMER_ABSTIME 1

#define GRND_RANDOM 0x02
#define GRND_NONBLOCK 0x01

// ░░░ Structs ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

typedef struct TIMESPEC
{
	uint64_t tv_sec;
	uint64_t tv_nsec;
} TIMESPEC;

// ░░░ Syscall Wrapper ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

// https://man7.org/linux/man-pages/man2/exit.2.html
__attribute__((noreturn))
static inline void exit(uint8_t status)
{
	syscall1(60, status);
	__builtin_unreachable();
}

// https://manpages.debian.org/unstable/manpages-dev/getrandom.2.en.html
static inline int64_t getrandom(void* buffer, uint64_t size, uint32_t flags)
{
	return (int64_t)syscall3(318, (uint64_t)buffer, size, flags);
}

// https://man7.org/linux/man-pages/man2/mmap.2.html
static inline int32_t munmap(void* addr, uint64_t length)
{
	return (int32_t)syscall2(11, (uint64_t)addr, length);
}

//__attribute__((malloc, malloc(munmap, 1)))
static inline void* mmap(void* addr, uint64_t length, uint32_t prot, uint32_t flags, uint32_t fd, uint64_t offset)
{
	return (void*)syscall6(9, (uint64_t)addr, length, prot, flags, fd, offset);
}

// https://manpages.debian.org/unstable/manpages-dev/write.2.en.html
static inline int64_t write(uint32_t fd, const void* buf, uint64_t count)
{
	return (int64_t)syscall3(1, fd, (uint64_t)buf, count);
}

// https://manpages.debian.org/unstable/manpages-dev/clock_nanosleep.2.en.html
static inline int64_t clock_nanosleep(uint32_t clockid, uint32_t flags, const TIMESPEC* t, TIMESPEC* remain)
{
	return (int64_t)syscall4(230, clockid, flags, (uint64_t)t, (uint64_t)remain);
}

// https://manpages.debian.org/unstable/manpages-dev/read.2.en.html
static inline int64_t read(uint32_t fd, void* buf, uint64_t count)
{
	return (int64_t)syscall3(0, fd, (uint64_t)buf, count);
}