.section .bss
stack_bottom: .skip 0x8000
stack_top:

.section .init

.option norvc

.type start, @function
.global start
start:
	.cfi_startproc
.option push
.option norelax
	la gp, global_pointer
.option pop

	csrw satp, zero
	la sp, stack_top

	la t0, main
	csrw mepc, t0
	tail __bootup
.loop:
	j .loop

.cfi_endproc
.end
