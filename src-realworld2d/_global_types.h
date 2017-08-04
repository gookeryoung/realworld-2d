#ifndef GLOBAL_TYPES_H
#define GLOBAL_TYPES_H

#include <stdint.h>

// Basic type definitions
typedef int8_t gint8;
typedef uint8_t guint8;
typedef int16_t gint16;
typedef uint16_t guint16;
typedef int32_t gint32;
typedef uint32_t guint32;
typedef int64_t gint64;
typedef uint64_t guint64;
typedef float gfloat;
typedef double gdouble;

// bool types
typedef uint8_t gbool;
#define GKTRUE   1
#define GKFALSE  0

#endif // GLOBAL_TYPES_H
