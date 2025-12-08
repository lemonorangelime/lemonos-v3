#pragma once

#define MODULE __attribute__((section(".modules")))

typedef int (* module_init_t)();

typedef struct {
	char * name;
	module_init_t init;
} module_t;

extern module_t __modsym;
extern module_t __modsym_end;

void module_init();
