#include <stdint.h>
#include <main.h>

int __bootup(uint32_t eax, uint32_t ebx) {
	main();
}
