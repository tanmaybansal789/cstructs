#ifndef CSTRUCTS_TYPES_H
#define CSTRUCTS_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef size_t usize;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef uint8_t byte;

typedef struct {
    char* data;
    u32 length;
} len_string_t;

#endif //CSTRUCTS_TYPES_H
