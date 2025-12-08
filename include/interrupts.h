#pragma once

#include <platform.h>

typedef void (* interrupt_handler_t)(interrupt_state_t * state);

void interrupts_init();
void asm_interrupts_init();
void interrupts_disable();
void interrupts_register(int number, interrupt_handler_t handler);
