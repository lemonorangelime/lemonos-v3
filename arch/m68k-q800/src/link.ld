ENTRY(start)
SECTIONS
	{
		. = 0x0;
		_kernel_start = ALIGN(8);
		.text : {
			*(.init)
			*(.text)
		}
		.bss : {*(.bss)}
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
