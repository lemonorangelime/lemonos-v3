#include <stdint.h>

void outb(uint16_t port, uint8_t d) {
	asm volatile ("outb %0, %1" :: "a"(d), "Nd"(port) : "memory");
}

void outw(uint16_t port, uint16_t d) {
	asm volatile ("outw %0, %1" :: "a"(d), "Nd"(port) : "memory");
}

void outd(uint16_t port, uint32_t d) {
	asm volatile ("outl %0, %1" :: "a"(d), "Nd"(port) : "memory");
}


uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

uint32_t ind(uint16_t port) {
	uint32_t ret;
	asm volatile ("inl %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}
