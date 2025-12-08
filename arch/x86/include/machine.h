#pragma once

#include <stddef.h>
#include <cpu/mmu.h>

extern size_t page_size;

#define MACHINE_NAME "IBM PC"

#define PDT_ADDR 0x00071000
#define PT_ADDR 0x00072000

static page_entry_t * pdt = (page_entry_t *) PDT_ADDR;
static page_entry_t * pt = (page_entry_t *) PT_ADDR;
