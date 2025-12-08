#pragma once

#include <stdint.h>

void serial_init();
void serial_write(char c);
void serial_print(char * s);
void serial_print_decimal(int number);
void serial_print_hex(uint64_t number);
