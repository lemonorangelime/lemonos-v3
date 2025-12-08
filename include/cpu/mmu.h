#pragma once

#include <stdint.h>
#include <stddef.h>
#include <vars.h>

typedef struct {
	uint64_t present : 1;
	uint64_t writable : 1;
	uint64_t supervisor : 1;
	uint64_t write_through: 1;
	uint64_t cache_disable : 1;
	uint64_t accessed : 1;
	uint64_t available_low : 1;
	uint64_t zero1 : 1;
	uint64_t available_mid : 4;
	uint64_t address : 35;
	uint64_t zero2 : 1;
	uint64_t available_high : 11;
	uint64_t executable : 1;
} __attribute__((packed)) page_entry_t;

typedef struct {
	uint32_t present : 1;
	uint32_t writable : 1;
	uint32_t supervisor : 1;
	uint32_t write_through: 1;
	uint32_t cache_disable : 1;
	uint32_t accessed : 1;
	uint32_t dirty : 1;
	uint32_t pat : 1;
	uint32_t global : 1;
	uint32_t available_low : 3;
	uint32_t address : 20;
} __attribute__((packed)) page_entry32_t;

// mmu.asm
void invalidate_page(void * p);

// mmu.c
int mmu_is_supported();
void * mmu_page_table_unwind(void * table, int index);
void * mmu_page_table_unwind_all(void * table, uint64_t address);
uint64_t mmu_get_phys_addr(void * p);
int mmu_map_page(void * to, uint64_t from);
int mmu_is_page_mapped(void * p);

void * mmu_alloc_page();
int mmu_free_page(void * page);
