#pragma once

#include <stdint.h>
#include <stddef.h>

void * memset(void * dest, int s, size_t size);
void * memset16(void * dest, uint16_t s, size_t size);
void * memset24(void * dest, uint32_t s, size_t size); // (s & 0xffffff)
void * memset32(void * dest, uint32_t s, size_t size);
void * memset64(void * dest, uint64_t s, size_t size);

void * memcpy(void * dest, void * src, size_t size);
void * memcpy16(void * dest, void * src, size_t size);
void * memcpy24(void * dest, void * src, size_t size);
void * memcpy32(void * dest, void * src, size_t size);
void * memcpy64(void * dest, void * src, size_t size);
