.section .bss
stack_bottom: .skip 0x8000
stack_top:

.section .init

.global start
start:
	move.l stack_top, %sp
	jsr __bootup
.loop:
	jmp .loop
