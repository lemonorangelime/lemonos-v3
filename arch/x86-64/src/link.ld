OUTPUT_FORMAT(elf64-x86-64)
ENTRY(start)
SECTIONS
	{
		. = 0x100000;
		_kernel_start = ALIGN(8);
		.multiboot : { *(.multiboot) }
		.text : {
			. = ALIGN(8);
			*(.text)
		}
		.bss : { *(.bss) }
		.data :{
			*(.data)
		}
		.modules : {
			__modsym = .;
			*(.modules)
			__modsym_end = .;
		}
	}
_kernel_end = ALIGN(8);
_kernel_size = _kernel_end - _kernel_start;
