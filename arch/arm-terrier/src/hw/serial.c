#include <stdint.h>

volatile uint8_t * uart = (volatile uint8_t *) 0x40100000;

void serial_init() {
}

void serial_write(uint8_t c) {
	uart[0] = c;
}

void serial_print(char * s) {
	while (*s) { serial_write(*s++); }
}

void serial_print_decimal(int number) {
	char buffer[32];
	int i = 0;
	while (number) {
		buffer[i++] = (number % 10) + '0';
		number /= 10;
	}

	while (i) {
		serial_write(buffer[--i]);
	}
}

void serial_print_hex(uint64_t number) {
	char hex_chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	int shift = 60;
	serial_print("0x");
	while (shift >= 0) {
		serial_write(hex_chars[(number >> shift) & 0xf]);
		shift -= 4;
	}
}
