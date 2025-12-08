#pragma once

#include <stdint.h>

void outb(uint16_t port, uint8_t d);
void outw(uint16_t port, uint16_t d);
void outd(uint16_t port, uint32_t d);

uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t ind(uint16_t port);
