ENTRY(start)
SECTIONS
	{
		. = 0x80003100;
		_kernel_start = .;
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
