// am i doing this right?

#include <hw/serial.h>
#include <cpu/mmu.h>
#include <stdint.h>
#include <stddef.h>

int pae_supported = 0;

void * mmu_page_table_unwind(void * table, int index) {
	page_entry_t * entry = &((page_entry_t *) table)[index];
	if (!entry->present) {
		return NULL;
	}
	return (page_entry_t *) (uintptr_t) (entry->address << 12);
}

void * mmu_page_table_unwind_all(void * table, uint64_t address) {
	int pml4t_index = (address >> 39) & 0x01ff;
	int pdpt_index = (address >> 31) & 0x01ff;
	int pdt_index = (address >> 21) & 0x01ff;
	int pt_index = (address >> 12) & 0x01ff;
	int indices[3] = {pml4t_index, pdpt_index, pdt_index};
	for (int i = 0; i < 3; i++) {
		table = mmu_page_table_unwind(table, indices[i]);
		if (!table) {
			return NULL;
		}
	}
	return &((page_entry_t *) table)[pt_index];
}

uint64_t mmu_get_phys_addr(void * p) {
	uintptr_t address = (uintptr_t) p;
	page_entry_t * table = mmu_page_table_unwind_all(pml4t, address);
	if (!table) {
		return 0;
	}
	return table->address << 12;
}

int mmu_map_page(void * to, uint64_t from) { // from physical
	// todo: allocate missing tables
	page_entry_t * table = mmu_page_table_unwind_all(pml4t, (uintptr_t) to);
	if (!table) {
		return 0;
	}
	table->address = from >> 12;
	table->present = 1;
	table->writable = 1;
	invalidate_page(to);
	return 1;
}

int mmu_is_page_mapped(void * p) {
	page_entry_t * table = mmu_page_table_unwind_all(pml4t, (uintptr_t) p);
	if (!table) {
		return 0;
	}
	return table->present;
}
