#pragma once

#define __X86
#define __X86_32

#include <stdint.h>

typedef struct {
        uint32_t eip;
        uint32_t eax;
        uint32_t ebx;
        uint32_t ecx;
        uint32_t edx;
        uint32_t esi;
        uint32_t edi;
        uint32_t ebp;
        uint32_t esp;
        uint32_t eflags;
        uint16_t cs;
        uint16_t ds;
        uint16_t ss;
        uint16_t es;
        uint16_t fs;
        uint16_t gs;
} __attribute__((packed)) registers_t;

typedef struct {
	registers_t registers;
} interrupt_state_t;
