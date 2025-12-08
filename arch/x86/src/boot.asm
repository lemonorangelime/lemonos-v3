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

PDPT equ 0x00071000
PDT equ 0x00072000
PT equ 0x00073000

gdt:
	dd 0x00000000, 0x00000000
	dd 0x0000ffff, 0x00cf9a00
	dd 0x0000ffff, 0x00cf9200
	dd 0x0000ffff, 0x00cfba00
	dd 0x0000ffff, 0x00cfb200
	dd 0x0000ffff, 0x00cfda00
	dd 0x0000ffff, 0x00cfd200
	dd 0x0000ffff, 0x00cffa00
	dd 0x0000ffff, 0x00cff200
gdt_end:
gdt_ptr:
	dw gdt_end - gdt - 1
	dd gdt, 0, 0, 0

no_paging:
	jmp halt

extern pae_supported

global start
extern start
extern __bootup
start:
	cli
	clts
	mov esp, stack_top

	push ebx
	push eax

	mov edi, PDPT
	xor eax, eax
	mov ecx, 0x2000
.clean: mov DWORD [edi], 0
	add edi, 4
	loop .clean

	mov eax, 1
	cpuid
	test edx, 1 << 6
	jz no_pae

	mov DWORD [pae_supported], 1

	mov edi, PDPT
	mov cr3, edi

	mov DWORD [PDPT], PDT | 0b1
	mov DWORD [PDT],  (PT) | 0b1
	mov DWORD [PDT + 8],  (PT + 0x1000) | 0b1
	mov DWORD [PDT + 16],  (PT + 0x2000) | 0b1
	mov DWORD [PDT + 24],  (PT + 0x3000) | 0b1

	mov edi, PT
	mov ebx, 0b11
	mov ecx, 1024 * 4
.create_entry:
	mov DWORD [edi], ebx
	add ebx, 0x1000
	add edi, 8
	loop .create_entry

	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	mov eax, cr0
	or eax, (1 << 31) | 1
	mov cr0, eax

	lgdt [gdt_ptr]
	jmp 8:pm32

no_pae:
	mov edi, PDT
	mov cr3, edi

	mov DWORD [PDT],  (PT) | 0b11
	mov DWORD [PDT + 4],  (PT + 0x1000) | 0b11
	mov DWORD [PDT + 8],  (PT + 0x2000) | 0b11
	mov DWORD [PDT + 12],  (PT + 0x3000) | 0b11

	mov edi, PT
	mov ebx, 0b11
	mov ecx, 1024 * 4
.create_entry:
	mov DWORD [edi], ebx
	add ebx, 0x1000
	add edi, 4
	loop .create_entry

	mov eax, cr0
	or eax, (1 << 31) | 1
	mov cr0, eax

	lgdt [gdt_ptr]
	jmp 8:pm32

pm32:
	mov ax, 16
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	call __bootup
	cli
halt:
	hlt
	jmp halt

