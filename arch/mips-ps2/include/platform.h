#pragma once

#define __ARM
#define __ARM32

#include <stdint.h>

typedef struct {
	uint32_t r1;
} __attribute__((packed)) registers_t;

typedef struct {
	registers_t registers;
} interrupt_state_t;
