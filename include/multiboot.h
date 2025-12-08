#pragma once

// multiboot should NOT be required, please provide a way to get this information without any bootloader help if possible

#include <stdint.h>

typedef struct {
	uint32_t start;
	uint32_t end;
	char * name;
} __attribute__((packed)) multiboot_module_t;

typedef struct {
	uint64_t start;
	uint64_t length;
	uint32_t type;
} __attribute__((packed)) multiboot_memory_map_t;

typedef struct {
	uint64_t size;
	uint8_t number;
	uint8_t mode;
	uint16_t cylinders;
	uint8_t sectors;
} __attribute__((packed)) multiboot_drive_t;

typedef struct {
	uint16_t version;
	uint16_t cs;
	uint32_t eip;
	uint16_t cs16;
	uint16_t ds;
	uint16_t flags;
	uint16_t cs_length;
	uint16_t cs16_length;
	uint16_t ds_length;
} __attribute__((packed)) apm_table_t;

typedef struct {
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	uint32_t boot_device;
	uint32_t cmdline;
	uint32_t mods_count;
	uint32_t modules;
	uint32_t tabsize;
	uint32_t strsize;
	uint32_t addr;
	uint32_t reserved0;
	uint32_t memory_map_size;
	uint32_t memory_map;
	uint32_t drive_map_length;
	uint32_t drive_map;
	uint32_t configuration;
	uint32_t bootloader_name;
	uint32_t apm_table;
	uint32_t vbe_info;
	uint32_t vbe_mode_info;
	uint16_t vbe_mode;
	uint16_t vbe_interface_cs;
	uint16_t vbe_interface_eip;
	uint16_t vbe_interface_length;
	uint64_t framebuffer;
	uint32_t framebuffer_pitch;
	uint32_t framebuffer_width;
	uint32_t framebuffer_height;
	uint8_t framebuffer_bpp;
	uint16_t framebuffer_type;
} __attribute__((packed)) multiboot_header_t;
