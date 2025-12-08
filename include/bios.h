#pragma once

#include <stdint.h>

typedef struct {
	uint8_t dual_bus : 1;
	uint8_t microchannel : 1;
	uint8_t ebda_present : 1;
	uint8_t wait_supported : 1;
	uint8_t int15h_4h_on_int09h : 1;
	uint8_t rtc_present : 1;
	uint8_t second_pics : 1;
	uint8_t dma3_assigned_to_disk : 1;
} __attribute__((packed)) bios_feat1_t;

typedef struct {
	uint8_t reserved : 1;
	uint8_t streaming_supported : 1;
	uint8_t non_8042_keyboard : 1;
	uint8_t int15h_c8_supported : 1;
	uint8_t int15h_c7_supported : 1;
	uint8_t int15h_c6_supported : 1;
	uint8_t int16h_09_supported : 1;
	uint8_t dma32_supported : 1;
} __attribute__((packed)) bios_feat2_t;

typedef struct {
	uint8_t scsi_iml_supported : 1;
	uint8_t iml_supported : 1;
	uint8_t op_panel_present : 1; // is this reliable ?
	uint8_t scsi_supported : 1;
	uint8_t rom_to_ram_supported : 1;
} __attribute__((packed)) bios_feat3_t;

typedef struct {
	uint8_t postext_supported : 1;
	uint8_t high_mem_split : 1;
	uint8_t reserved : 1;
	uint8_t abios_configuration : 3;
	uint8_t eeprom_present : 1; // fucking where
} __attribute__((packed)) bios_feat4_t;

typedef struct {
	uint8_t flashable_bios : 1;
	uint8_t enhanced_mouse : 1;
} __attribute__((packed)) bios_feat5_t;

typedef struct {
	uint16_t size;
	uint8_t model;
	uint8_t submodel;
	uint8_t revision;
	bios_feat1_t feature1;
	bios_feat2_t feature2;
	bios_feat3_t feature3;
	bios_feat4_t feature4;
	bios_feat5_t feature5;
	uint8_t extended_data[];
} __attribute__((packed)) bios_configuration_t;

typedef struct {
	char signature[4];
	uint16_t version;
	char * oem_string;
	uint32_t capabilites;
	void * video_mode;
	uint16_t vram;
	uint16_t vbe_revision;
	char * vendor_name;
	char * product_name;
	uint32_t * product_revision; // why is this a pointer?
	uint8_t vbe_data[222];
	uint8_t oem_data[255];
} __attribute__((packed)) vbe_configuration_t;
