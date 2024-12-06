.data
	g_a: .word 2
	g_b: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	g_c: .byte 0
	g_d: .byte 0:10
	g_dqr0: .asciiz "This is a string"


.text
	jal func_main
	li $v0, 10
	syscall

func_main:
	sw $ra, -4($sp)
func_main_block_0:
	la $t8, g_dqr0($zero)
	sw $t8, -8($sp)
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	li $a0, 10
	li $v0, 11
	syscall
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
