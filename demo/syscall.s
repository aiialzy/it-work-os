	.section .rodata
.LC0:
	.string "Hello, World!\n"	

	.section .text
    .globl sys_call
sys_call:
    mv a7, a0
    ld a0, 0(a1)
    ld a2, 16(a1)
    ld a1, 8(a1)
    ecall
    ret

	.globl _start
_start:
	addi 	sp, sp, -40
	li		a5, 1
	sd		a5, 8(sp)
	lui		a5, %hi(.LC0)
	addi	a5, a5, %lo(.LC0)
	sd		a5, 16(sp)
	li		a5, 14
	sd		a5, 24(sp)
	li		a0, 64
	addi	a1, sp, 8
	sd		ra, 40(sp)
	call	sys_call
	ld		ra, 40(sp)

	li		a5, 0
	sd		a5, 8(sp)	
	sd		a5, 16(sp)	
	sd		a5, 24(sp)	
	li		a0, 93
	addi	a1, sp, 8
	sd		ra, 40(sp)
	call 	sys_call
	ld		ra, 40(sp)

	addi	sp, sp, 48
	li		a0, 0
	ret
