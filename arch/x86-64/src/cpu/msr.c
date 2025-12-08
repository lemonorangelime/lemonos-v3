#include <stdint.h>

uint64_t rdmsr(uint32_t ecx) {
	uint64_t value;
	asm volatile ("rdmsr" : "=A"(value) : "c"(ecx));
	return value;
}

void wrmsr(uint32_t ecx, uint64_t value) {
	asm volatile ("wrmsr" :: "A"(value), "c"(ecx));
}
