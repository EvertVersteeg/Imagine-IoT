ENTRY(Reset_Handler)

MEMORY
{
	FLASH(rx):ORIGIN =0x08000000,LENGTH =1024K
	SRAM(rwx):ORIGIN =0x20000000,LENGTH =128K
}

__max_heap_size = 0x400;
__max_stack_size = 0x200;

SECTIONS
{
	.text :
	{
		*(.isr_vector)
		*(.text)
		*(.rodata)
		. = ALIGN(4);
		_etext = .;
	}> FLASH
	
	.data :
	{
		_sdata = .;
		*(.data)
		. = ALIGN(4);
		_edata = .;
	}> SRAM AT> FLASH
	
	.dbss :
	{
		_sbss = .;
		*(.bss)
		. = ALIGN(4);
		_ebss = .;
	}> SRAM
}