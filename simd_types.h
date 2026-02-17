#pragma once
#include "types.h"

// https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html

// ░░░ Signed Integers ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

typedef int8_t    int8x16_t  __attribute__((vector_size(16)));
typedef int16_t   int16x8_t  __attribute__((vector_size(16)));
typedef int32_t   int32x4_t  __attribute__((vector_size(16)));
typedef int64_t   int64x2_t  __attribute__((vector_size(16)));

typedef int8_t    int8x32_t  __attribute__((vector_size(32)));
typedef int16_t   int16x16_t __attribute__((vector_size(32)));
typedef int32_t   int32x8_t  __attribute__((vector_size(32)));
typedef int64_t   int64x4_t  __attribute__((vector_size(32)));

typedef int8_t    int8x64_t  __attribute__((vector_size(64)));
typedef int16_t   int16x32_t __attribute__((vector_size(64)));
typedef int32_t   int32x16_t __attribute__((vector_size(64)));
typedef int64_t   int64x8_t  __attribute__((vector_size(64)));

// ░░░ Unsigned Integers ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

typedef uint8_t   uint8x16_t  __attribute__((vector_size(16)));
typedef uint16_t  uint16x8_t  __attribute__((vector_size(16)));
typedef uint32_t  uint32x4_t  __attribute__((vector_size(16)));
typedef uint64_t  uint64x2_t  __attribute__((vector_size(16)));

typedef uint8_t   uint8x32_t  __attribute__((vector_size(32)));
typedef uint16_t  uint16x16_t __attribute__((vector_size(32)));
typedef uint32_t  uint32x8_t  __attribute__((vector_size(32)));
typedef uint64_t  uint64x4_t  __attribute__((vector_size(32)));

typedef uint8_t   uint8x64_t  __attribute__((vector_size(64)));
typedef uint16_t  uint16x32_t __attribute__((vector_size(64)));
typedef uint32_t  uint32x16_t __attribute__((vector_size(64)));
typedef uint64_t  uint64x8_t  __attribute__((vector_size(64)));

// ░░░ Floatingpoint ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

typedef halve_t f16x8_t  __attribute__((vector_size(16)));
typedef halve_t f16x16_t __attribute__((vector_size(32)));
typedef halve_t f16x32_t __attribute__((vector_size(64)));

typedef single_t f32x4_t  __attribute__((vector_size(16)));
typedef single_t f32x8_t  __attribute__((vector_size(32)));
typedef single_t f32x16_t __attribute__((vector_size(64)));

typedef double_t f64x2_t  __attribute__((vector_size(16)));
typedef double_t f64x4_t  __attribute__((vector_size(32)));
typedef double_t f64x8_t  __attribute__((vector_size(64)));
