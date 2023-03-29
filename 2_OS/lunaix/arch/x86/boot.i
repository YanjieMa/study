# 1 "boot.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "boot.S"
# 1 "multiboot.h" 1
# 2 "boot.S" 2

.section .multiboot
 .long 0x1BADB002
 .long 0x03
 .long -(0x1BADB002 +0x03)

.section .bss

 .align 16
 stack_bottom:
  .skip 16318, 0
 stack_top:


.section .text
 .global start_
 start_:
  movl $stack_top, %esp






  call _kernel_init

  pushl %ebx
  call _kernel_main


  cli


 j_:
  hlt
  jmp j_
