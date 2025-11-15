#pragma once

#include <platform.h>
#include <stdint.h>

#if defined(__X86_64)
typedef uint64_t uintptr_t;
typedef int64_t intptr_t;
#elif defined(__X86)
typedef uint32_t uintptr_t;
typedef int32_t intptr_t;
#endif

#define NULL ((void *) 0)
