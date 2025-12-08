#include <hw/serial.h>
#include <cpu/mmu.h>
#include <stdint.h>
#include <stddef.h>

void * mmu_page_table_unwind(void * table, int index) {
	return NULL;
}

void * mmu_page_table_unwind_all(void * table, uint64_t address) {
	return NULL;
}

uint64_t mmu_get_phys_addr(void * p) {
	return 0;
}

int mmu_map_page(void * to, uint64_t from) { // from physical
	return 0;
}

int mmu_is_page_mapped(void * p) {
	return 0;
}
