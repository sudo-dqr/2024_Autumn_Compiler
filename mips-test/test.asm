.data
	g_dqr0: .asciiz "c is "
	g_dqr1: .asciiz ", d is "
	g_dqr2: .asciiz "\n"


.text
	jal func_main
	li $v0, 10
	syscall

func_main:
	sw $ra, -4($sp)
func_main_block_0:
	li $t8, 1
	sw $t8, -8($sp)
	li $t8, 2
	sw $t8, -12($sp)
	lw $t0, -8($sp)
	lw $t1, -12($sp)
	addu $t2, $t0, $t1
	sw $t2, -16($sp)
	lw $t3, -16($sp)
	lw $t4, -8($sp)
	addu $t5, $t3, $t4
	sw $t5, -20($sp)
	lw $t6, -16($sp)
	lw $t7, -20($sp)
	la $t8, g_dqr0($zero)
	addu $s0, $t8, $zero
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	addu $a0, $t6, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr1($zero)
	addu $s1, $t8, $zero
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	addu $a0, $t7, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr2($zero)
	addu $s2, $t8, $zero
	la $a0, g_dqr2($zero)
	li $v0, 4
	syscall
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
