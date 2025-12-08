#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct memory_slot {
	uintptr_t start; // we have a whole page so why not store this redundant info
	uintptr_t end;
	size_t size;
	struct memory_slot * next;
} memory_slot_t;

memory_slot_t * memory_setup_slot(memory_slot_t * previous_slot, uintptr_t address, size_t size);
