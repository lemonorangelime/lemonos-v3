.section .bss
stack_bottom: .skip 0x8000
stack_top:

.section .init

header:

.global start
start:
	b start
/*
	ldr sp, =stack_top

	bl __bootup
.loop:
	b .loop
*/
