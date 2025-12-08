#pragma once

#include <platform.h>
#include <stdint.h>

// make this long preprocessor shit a simple typedef in platform.h

#if defined(__X86_64)
typedef uint64_t uintptr_t;
typedef int64_t intptr_t;
#elif defined(__X86_32)
typedef uint32_t uintptr_t;
typedef int32_t intptr_t;
#endif

#if defined(__RISCV64)
typedef uint64_t uintptr_t;
typedef int64_t intptr_t;
#elif defined(__RISCV32)
typedef uint32_t uintptr_t;
typedef int32_t intptr_t;
#endif

#if defined(__ARM32)
typedef uint32_t uintptr_t;
typedef int32_t intptr_t;
#elif defined(__ARM64)
typedef uint64_t uintptr_t;
typedef int64_t intptr_t;
#endif

#if defined(__MIPS32)
typedef uint32_t uintptr_t;
typedef int32_t intptr_t;
#elif defined(__MIPS64)
typedef uint64_t uintptr_t;
typedef int64_t intptr_t;
#endif

#if defined(__M68K)
typedef uint32_t uintptr_t;
typedef int32_t intptr_t;
#endif

typedef uintptr_t size_t;
typedef intptr_t ssize_t;

#define NULL ((void *) 0)
