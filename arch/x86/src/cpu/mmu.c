// am i doing this right?

#include <hw/serial.h>
#include <machine.h>
#include <cpu/mmu.h>
#include <stdint.h>
#include <stddef.h>

int pae_supported = 0;

void * __pae_mmu_page_table_unwind(void * table, int index) {
	page_entry_t * entry = &((page_entry_t *) table)[index];
	if (!entry->present) {
		return NULL;
	}
	return (void *) (uintptr_t) (entry->address << 12);
}

void * __mmu_page_table_unwind(void * table, int index) {
	page_entry32_t * entry = &((page_entry32_t *) table)[index];
	if (!entry->present) {
		return NULL;
	}
	return (void *) (uintptr_t) (entry->address << 12);
}

void * mmu_page_table_unwind(void * table, int index) {
	return pae_supported ? __pae_mmu_page_table_unwind(table, index) : __mmu_page_table_unwind(table, index);
}

void * __pae_mmu_page_table_unwind_all(void * table, uint64_t address) {
	int pdpt_index = (address >> 31) & 0x01ff;
	int pdt_index = (address >> 21) & 0x01ff;
	int pt_index = (address >> 12) & 0x01ff;
	int indices[2] = {pdpt_index, pdt_index};
	for (int i = 0; i < 2; i++) {
		table = mmu_page_table_unwind(table, indices[i]);
		if (!table) {
			return NULL;
		}
	}
	return &((page_entry_t *) table)[pt_index];
}

void * __mmu_page_table_unwind_all(void * table, uint64_t address) {
	int pdt_index = (address >> 21) & 0x01ff;
	int pt_index = (address >> 12) & 0xfffff;
	table = mmu_page_table_unwind(table, pdt_index);
	if (!table) {
		return NULL;
	}
	return &((page_entry32_t *) table)[pt_index];
}

void * mmu_page_table_unwind_all(void * table, uint64_t address) {
	return pae_supported ? __pae_mmu_page_table_unwind_all(table, address) : __mmu_page_table_unwind_all(table, address);
}

uint64_t __pae_mmu_get_phys_addr(void * p) {
	uintptr_t address = (uintptr_t) p;
	page_entry_t * table = mmu_page_table_unwind_all(pdpt, address);
	if (!table) {
		return 0;
	}
	return table->address << 12;
}

uint64_t __mmu_get_phys_addr(void * p) {
	uintptr_t address = (uintptr_t) p;
	page_entry32_t * table = mmu_page_table_unwind_all(pdt, address);
	if (!table) {
		return 0;
	}
	return table->address << 12;
}

uint64_t mmu_get_phys_addr(void * p) {
	return pae_supported ? __pae_mmu_get_phys_addr(p) : __mmu_get_phys_addr(p);
}

int __pae_mmu_map_page(void * to, uint64_t from) { // from physical
	// todo: allocate missing tables
	page_entry_t * table = mmu_page_table_unwind_all(pdpt, (uintptr_t) to);
	if (!table) {
		return 0;
	}
	table->address = from >> 12;
	table->present = 1;
	table->writable = 1;
	invalidate_page(to);
	return 1;
}

int __mmu_map_page(void * to, uint64_t from) { // from physical
	// todo: allocate missing tables
	if (from & 0xffffffff00000000) {
		return 0;
	}
	page_entry32_t * table = mmu_page_table_unwind_all(pdt, (uintptr_t) to);
	if (!table) {
		return 0;
	}
	table->address = from >> 12;
	table->present = 1;
	table->writable = 1;
	invalidate_page(to);
	return 1;
}

int mmu_map_page(void * to, uint64_t from) { // from physical
	return pae_supported ? __pae_mmu_map_page(to, from) : __mmu_map_page(to, from);
}

int __pae_mmu_is_page_mapped(void * p) {
	page_entry_t * table = mmu_page_table_unwind_all(pdpt, (uintptr_t) p);
	if (!table) {
		return 0;
	}
	return table->present;
}

int __mmu_is_page_mapped(void * p) {
	page_entry32_t * table = mmu_page_table_unwind_all(pdt, (uintptr_t) p);
	if (!table) {
		return 0;
	}
	return table->present;
}

int mmu_is_page_mapped(void * p) {
	return pae_supported ? __pae_mmu_is_page_mapped(p) : __mmu_is_page_mapped(p);
}
