#include <stdint.h>

// i have become a big macro enthusist
#define memset_generic(type, dest, s, size) \
	type * p = dest; \
	while (size--) { *p++ = s; } \
	return dest; \

#define memcpy_generic(type, dest, src, size) \
	type * d = dest; \
	type * s = src; \
	while (size--) { *d++ = *s++; } \
	return dest; \



void * memset(void * dest, int s, size_t size) {
	memset_generic(uint8_t, dest, s, size);
}

void * memset16(void * dest, uint16_t s, size_t size) {
	memset_generic(uint8_t, dest, s, size);
}

void * memset24(void * dest, uint32_t s, size_t size) {
	uint8_t * p = dest;
	while (size--) {
		*p++ = s & 0xff;
		*p++ = (s >> 8) & 0xff;
		*p++ = (s >> 16) & 0xff;
	}
	return dest;
}

void * memset32(void * dest, uint32_t s, size_t size) {
	memset_generic(uint32_t, dest, s, size);
}

void * memset64(void * dest, uint64_t s, size_t size) {
	memset_generic(uint64_t, dest, s, size);
}

void * memcpy(void * dest, void * src, size_t size) {
	memcpy_generic(uint8_t, dest, src, size);
}

void * memcpy16(void * dest, void * src, size_t size) {
	memcpy_generic(uint16_t, dest, src, size);
}

void * memcpy24(void * dest, void * src, size_t size) {
	uint8_t * d = dest;
	uint8_t * s = src;
	while (size--) {
		*p++ = *s++;
		*p++ = *s++;
		*p++ = *s++;
	}
	return dest;
}

void * memcpy32(void * dest, void * src, size_t size) {
	memcpy_generic(uint32_t, dest, src, size);
}

void * memcpy64(void * dest, void * src, size_t size) {
	memcpy_generic(uint64_t, dest, src, size);
}
