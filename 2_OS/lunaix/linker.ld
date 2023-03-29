ENTRY(start_)

SECTIONS {
	. = 0x00100000;

	.text BLOCK(0x1000) : {
		* (.multiboot)
		* (.text)
	}
	
	.bss BLOCK(0x1000) : {
		* (COMMON)
		* (.bss)
	}
	
	.data BLOCK(0x1000) : {
		* (.data)
	}

	.rodata BLOCK(0x1000) : {
		* (.rodata)
	}
}
