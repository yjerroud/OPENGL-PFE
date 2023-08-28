#ifndef TOOLS_H
#define TOOLS_H
#include <stdint.h>

#define KILOBYTES(size) (1024LL * size)
#define MEGABYTES(size) (KILOBYTES(size) * 1024LL)
#define GIGABYTES(size) (MEGABYTES(size) * 1024LL)

typedef int64_t s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t 	s8;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef s32 b32;

typedef float  f32;
typedef double f64;

#endif