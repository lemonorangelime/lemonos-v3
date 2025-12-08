#include <module.h>

void module_init() {
	module_t * modsym = &__modsym;
	module_t * modsym_end = &__modsym_end;
	while (modsym < modsym_end) {
		modsym->init();
		modsym++;
	}
}
