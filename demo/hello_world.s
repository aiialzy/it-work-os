	.section .text
	.globl _start
_start:
	li		a0, 1
	la		a1, helloworld
	li		a2, 14
	li		a7, 64
	ecall
	li		a0, 0
	li		a1, 0
	li		a2, 0
	li		a7, 93
	ecall
	li 		a0, 0
	ret

	.section .data
helloworld:
	.string 	"Hello World!\n"
