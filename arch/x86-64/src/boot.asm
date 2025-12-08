align 4
section .multiboot
	dd 0x1badb002
	dd 0x07
	dd -(0x1badb002 + 0x07)
	dd 0
	dd 0
	dd 0
	dd 0
	dd 0
	dd 0
	dd 480
	dd 640
	dd 32

section .bss
stack_bottom: resb 65535
stack_top:

bits 32

section .text

PML4T equ 0x00070000
PDPT equ 0x00071000
PDT equ 0x00072000
PT equ 0x00073000

gdt:
	dd 0x00000000, 0x00000000
	dd 0x0000ffff, 0x00af9a00
	dd 0x0000ffff, 0x00cf9200
	dd 0x0000ffff, 0x00afba00
	dd 0x0000ffff, 0x00cfb200
	dd 0x0000ffff, 0x00afda00
	dd 0x0000ffff, 0x00cfd200
	dd 0x0000ffff, 0x00affa00
	dd 0x0000ffff, 0x00cff200
gdt_end:
gdt_ptr:
	dw gdt_end - gdt - 1
	dq gdt

no_long_mode:
	mov dx, 0x3f8
	mov al, 'E'
	out dx, al
	mov al, 'R'
	out dx, al
	mov al, 'R'
	out dx, al
	mov al, 0x0a
	out dx, al

	jmp halt

global start
extern start
extern __bootup
start:
	cli
	clts
	mov esp, stack_top

	push ebx
	push eax

	; this is a bit stolen but we just want to get into long mode, then do this on our own

	mov eax, 0x80000000
	cpuid
	cmp eax, 0x80000001
	jb no_long_mode
	mov eax, 0x80000001
	cpuid
	test edx, 1 << 29
	jz no_long_mode

	mov edi, PML4T
	mov cr3, edi

	xor eax, eax
	mov ecx, 0x2000
.clean: mov DWORD [edi], 0
	add edi, 4
	loop .clean

	mov DWORD [PML4T], PDPT | 0b11
	mov DWORD [PDPT], PDT | 0b11
	mov DWORD [PDT],  (PT) | 0b11
	mov DWORD [PDT + 8],  (PT + 0x1000) | 0b11
	mov DWORD [PDT + 16],  (PT + 0x2000) | 0b11
	mov DWORD [PDT + 24],  (PT + 0x3000) | 0b11

	mov edi, PT
	mov ebx, 0b11
	mov ecx, 512 * 4
.create_entry:
	mov DWORD [edi], ebx
	add ebx, 0x1000
	add edi, 8
	loop .create_entry

	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr

	mov eax, cr0
	or eax, (1 << 31) | 1
	mov cr0, eax

	lgdt [gdt_ptr]
	jmp 8:.long

bits 64
.long:
	mov ax, 16
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov edi, DWORD [rsp]
	add rsp, 4
	mov esi, DWORD [rsp]
	add rsp, 4

	call __bootup
	cli
halt:
	hlt
	jmp halt

