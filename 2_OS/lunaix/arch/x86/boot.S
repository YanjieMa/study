#include "multiboot.h"

.section .multiboot
	.long MB_MAGIC
	.long MB_ALIGNED_4K_MEM_MAP
	.long CHECKSUM

.section .bss
	/*惯例：必须16bytes对齐*/
	.align 16
	stack_bottom:
		.skip 16318, 0
	stack_top:
		

.section .text
	.global start_
	.type start_, @function
	start_:
		movl $stack_top, %esp
		/*
			todo:kernel init
				1.load GDT
				2.load IDT
				3.enable paging
		*/
		call _kernel_init

		pushl %ebx 
		call _kernel_main
		
		/*进制中断发生    sti 允许中断发生*/
		cli

		/*操作系统退出，系统hold循环*/
	j_:
		hlt
		jmp j_
