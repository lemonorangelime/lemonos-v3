#include <hw/serial.h>
#include <cpu/mmu.h>
#include <stdint.h>
#include <stddef.h>

int test_mapping(uintptr_t address) {
	void * p = (void *) address;
	int mapped = mmu_is_page_mapped(p);
	serial_print("Is ");
	serial_print_hex(address);
	serial_print(" mapped? ");
	serial_print(mapped ? "YES" : "NO");
	if (mapped) {
		serial_print(" (@ ");
		serial_print_hex(mmu_get_phys_addr(p));
		serial_print(")");
	}
	serial_print("\n");
	return mapped;
}

// mmu_is_page_mapped
int main(uint32_t eax, uint32_t ebx) {
	serial_print((sizeof(void *) == 8) ? "Hello from long mode!!!\n" : "Hello from 32 bit mode!!!\n");
	if (sizeof(void *) == 4) {
		serial_print(pae_supported ? "PAE supported\n\n" : "PAE unsupported\n\n");
	}

	volatile uint64_t * test_page = (uint64_t *) 0x000000ull;
	while (test_mapping((uintptr_t) test_page)) {
		test_page += 0x100000ull >> 3ull;
	}
	test_page -= 0x200000ull >> 3ull; // we can't yet allocate pages so we have to make sure this is a valid page

	serial_print("\nMapping ");
	serial_print_hex((uintptr_t) test_page);
	serial_print(" -> 0x001000\n\n");

	mmu_map_page((void *) test_page, 0x1000);
	test_mapping((uintptr_t) test_page);

	int match = 1;
	uint8_t * from = (uint8_t *) test_page;
	uint8_t * to = (uint8_t *) 0x1000;
	from[0] = 0x80; to[0] = 0x12;
	from[1] = 0xff; to[1] = 0x34;
	from[2] = 0x78; to[2] = 0x56;
	from[3] = 0x56; to[3] = 0x78;
	from[4] = 0x34; to[4] = 0xff;
	from[5] = 0x12; to[5] = 0x80;
	for (int i = 0; i < 0x1000; i++) {
		if ((*from++) != (*to++)) {
			match = 0;
			break;
		}
	}
	if (match) {
		serial_print("Pages ");
		serial_print_hex((uintptr_t) test_page);
		serial_print(" and 0x001000 match; PAGING WORKING\n");
	} else {
		serial_print("Pages ");
		serial_print_hex((uintptr_t) test_page);
		serial_print(" and 0x001000 don't match\n");
	}

	if (sizeof(void *) == 4) {
		if (!mmu_map_page((void *) test_page, 0x10000f000)) {
			serial_print("\nMapping error; PAE test failed\n");
		} else {
			serial_print("\nMapping ");
			serial_print_hex((uintptr_t) test_page);
			serial_print(" -> 0x10000f000\n\n");

			uint64_t * test = (uint64_t *) 0xf000;
			*test = 0xff;
			*test_page = 0x0102030405060708;
			if (*test_page == 0x0102030405060708 && *test == 0xff) {
				serial_print("Sucessfully wrote above 32 bit address limit; PAE WORKING\n");
			} else {
				serial_print("PAE test failed (requires above 4GB of ram)\n");
			}
		}
	}

	return 0;
}
