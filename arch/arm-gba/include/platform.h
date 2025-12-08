#pragma once

#define __ARM
#define __ARM32

#include <stdint.h>

typedef struct {
	// x0 hardwired zero
	uint32_t x1;
} __attribute__((packed)) registers_t;

typedef struct {
	registers_t registers;
} interrupt_state_t;
