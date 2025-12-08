#include <platform.h>
#include <machine.h>
#include <cpu/mmu.h>
#include <stddef.h>
#include <string.h>
#include <memory.h>

memory_slot_t * memory_slot = NULL;

memory_slot_t * memory_setup_slot(memory_slot_t * previous_slot, uintptr_t address, size_t size) {
	memory_slot_t * slot = (memory_slot_t *) address;
	slot->start = address;
	slot->end = address + size;
	slot->size = size;
	slot->next = NULL;
	if (previous_slot) {
		previous_slot->next = slot;
	}
	return slot;
}

int memory_init() {
	/*
	if (!mmu_is_supported()) {
		memset((void *) ram_start, 0, ram_end - ram_start);
		return 1;
	}

	void * page = mmu_alloc_page();
	uintptr_t p = ram_start;
	while (p < ram_end) {
		if (mmu_map_page(page, p)) {
			return 0; // fine
		}
		memset(page, 0, page_size);
		p += page_size;
	}
	mmu_free_page(page);
	return 1; // no error
	*/
}
