	.text
	.globl main
main:
	li		a0, 1
	la		a1, helloworld
	li		a2, 14
	li		a7, 64
	ecall
	li 		a0, 0
	ret

	.data
helloworld:
	.ascii 	"Hello World!\n"
