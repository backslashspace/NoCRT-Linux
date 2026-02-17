#pragma once
#include "types.h"

__attribute__((always_inline))
static inline uint16_t CheckErrno(int64_t code)
{
    if (code < 0 && code > -4096) return -(uint16_t)code;
    return 0;
}

/// <summary>
/// Written back to front - front bytes might be empty for small numbers
/// </summary>
/// <remarks>
/// To get the actually start use buffer + 20 - length | 20 is internal max length <br/>Version of <see href="https://gist.githubusercontent.com/lpereira/c0bf3ca3148321395037/raw/97aac8794c4c79321f1a102fc2c82d2b05c32878/gistfile1.cpp">facebook_fixed_test</see>
/// </remarks>
/// <param name="value">Input</param>
/// <param name="buffer">Buffer of length 20</param>
/// <returns>Length in visual digits</returns>
uint16_t UInt64ToChar(uint64_t value, char_t* buffer);