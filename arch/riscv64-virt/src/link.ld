ENTRY(start)
SECTIONS
	{
		. = 0x80000000;
		_kernel_start = .;
		.text : {
			*(.init)
			*(.text)
		}
		.bss : {*(.bss)}
		.data :{
			
			PROVIDE(global_pointer = . + 0x800);
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
