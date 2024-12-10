.data
	g_dqr0: .asciiz "\n"
	g_dqr1: .asciiz "\n"
	g_dqr2: .asciiz "\n"
	g_dqr3: .asciiz "\n"
	g_dqr4: .asciiz "\n"
	g_dqr5: .asciiz "\n"
	g_dqr6: .asciiz "\n"
	g_dqr7: .asciiz "\n"
	g_dqr8: .asciiz "\n"
	g_dqr9: .asciiz "\n"


.text
	jal func_main
	li $v0, 10
	syscall

func_getIndex:
	sw $ra, -4($sp)
func_getIndex_block_2:
	sw $a0, -8($sp)
	sw $a1, -12($sp)
	lw $t0, -8($sp)
	lw $t1, -12($sp)
	addu $t8, $t0, $zero
	sll $t1, $t1, 2
	addu $t8, $t8, $t1
	addu $t0, $t8, $zero
	lw $t1, 0($t0)
	addu $v0, $t1, $zero
	lw $ra, -4($sp)
	jr $ra
func_setIndex:
	sw $ra, -4($sp)
func_setIndex_block_3:
	sw $a0, -8($sp)
	sw $a1, -12($sp)
	sw $a2, -16($sp)
	lw $t0, -8($sp)
	lw $t1, -12($sp)
	addu $t8, $t0, $zero
	sll $t1, $t1, 2
	addu $t8, $t8, $t1
	addu $t0, $t8, $zero
	lw $t1, 0($t0)
	sw $t1, -32($sp)
	lw $t0, -8($sp)
	lw $t1, -12($sp)
	addu $t8, $t0, $zero
	sll $t1, $t1, 2
	addu $t8, $t8, $t1
	addu $t0, $t8, $zero
	lw $t1, -16($sp)
	sw $t1, 0($t0)
	lw $t0, -32($sp)
	addu $v0, $t0, $zero
	lw $ra, -4($sp)
	jr $ra
func_main:
	sw $ra, -4($sp)
func_main_block_0:
	la $t8, -24($sp)
	addu $t0, $t8, $zero
	li $t8, 0
	sw $t8, 0($t0)
	la $t8, -24($sp)
	addiu $t8, $t8, 4
	addu $t0, $t8, $zero
	li $t8, 1
	sw $t8, 0($t0)
	la $t8, -24($sp)
	addiu $t8, $t8, 8
	addu $t0, $t8, $zero
	li $t8, 2
	sw $t8, 0($t0)
	la $t8, -24($sp)
	addiu $t8, $t8, 12
	addu $t0, $t8, $zero
	li $t8, 3
	sw $t8, 0($t0)
	la $t8, -24($sp)
	addiu $t8, $t8, 16
	addu $t0, $t8, $zero
	li $t8, 4
	sw $t8, 0($t0)
	la $t8, -44($sp)
	addu $t0, $t8, $zero
	li $t8, 0
	sw $t8, 0($t0)
	la $t8, -44($sp)
	addiu $t8, $t8, 4
	addu $t0, $t8, $zero
	li $t8, 0
	sw $t8, 0($t0)
	la $t8, -44($sp)
	addiu $t8, $t8, 8
	addu $t0, $t8, $zero
	li $t8, 0
	sw $t8, 0($t0)
	la $t8, -44($sp)
	addiu $t8, $t8, 12
	addu $t0, $t8, $zero
	li $t8, 0
	sw $t8, 0($t0)
	la $t8, -44($sp)
	addiu $t8, $t8, 16
	addu $t0, $t8, $zero
	li $t8, 0
	sw $t8, 0($t0)
	la $t8, -44($sp)
	addu $t0, $t8, $zero
	la $t8, -24($sp)
	addu $t1, $t8, $zero
	sw $t0, -52($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -60
	addu $a0, $t1, $zero
	li $a1, 0
	jal func_getIndex
	addi $sp, $sp, 60
	lw $t0, -52($sp)
	addu $t1, $v0, $zero
	addu $fp, $sp, $zero
	addiu $sp, $sp, -64
	addu $a0, $t0, $zero
	li $a1, 0
	addu $a2, $t1, $zero
	jal func_setIndex
	addi $sp, $sp, 64
	addu $t0, $v0, $zero
	addu $a0, $t0, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr0($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	la $t8, -44($sp)
	addu $t1, $t8, $zero
	la $t8, -24($sp)
	addu $t2, $t8, $zero
	sw $t1, -52($sp)
	sw $t0, -56($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -64
	addu $a0, $t2, $zero
	li $a1, 1
	jal func_getIndex
	addi $sp, $sp, 64
	lw $t0, -56($sp)
	lw $t1, -52($sp)
	addu $t2, $v0, $zero
	addiu $t2, $t2, 1
	sw $t0, -56($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -68
	addu $a0, $t1, $zero
	li $a1, 1
	addu $a2, $t2, $zero
	jal func_setIndex
	addi $sp, $sp, 68
	lw $t0, -56($sp)
	addu $t1, $v0, $zero
	addu $a0, $t1, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr1($zero)
	addu $t1, $t8, $zero
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	la $t8, -44($sp)
	addu $t2, $t8, $zero
	la $t8, -24($sp)
	addu $t3, $t8, $zero
	sw $t2, -52($sp)
	sw $t1, -56($sp)
	sw $t0, -60($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -68
	addu $a0, $t3, $zero
	li $a1, 2
	jal func_getIndex
	addi $sp, $sp, 68
	lw $t0, -60($sp)
	lw $t1, -56($sp)
	lw $t2, -52($sp)
	addu $t3, $v0, $zero
	addiu $t3, $t3, 2
	sw $t1, -56($sp)
	sw $t0, -60($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -72
	addu $a0, $t2, $zero
	li $a1, 2
	addu $a2, $t3, $zero
	jal func_setIndex
	addi $sp, $sp, 72
	lw $t0, -60($sp)
	lw $t1, -56($sp)
	addu $t2, $v0, $zero
	addu $a0, $t2, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr2($zero)
	addu $t2, $t8, $zero
	la $a0, g_dqr2($zero)
	li $v0, 4
	syscall
	la $t8, -44($sp)
	addu $t3, $t8, $zero
	la $t8, -24($sp)
	addu $t4, $t8, $zero
	sw $t2, -52($sp)
	sw $t1, -56($sp)
	sw $t3, -60($sp)
	sw $t0, -64($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -72
	addu $a0, $t4, $zero
	li $a1, 3
	jal func_getIndex
	addi $sp, $sp, 72
	lw $t0, -64($sp)
	lw $t3, -60($sp)
	lw $t1, -56($sp)
	lw $t2, -52($sp)
	addu $t4, $v0, $zero
	addiu $t4, $t4, 3
	sw $t2, -52($sp)
	sw $t1, -56($sp)
	sw $t0, -64($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -76
	addu $a0, $t3, $zero
	li $a1, 3
	addu $a2, $t4, $zero
	jal func_setIndex
	addi $sp, $sp, 76
	lw $t0, -64($sp)
	lw $t1, -56($sp)
	lw $t2, -52($sp)
	addu $t3, $v0, $zero
	addu $a0, $t3, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr3($zero)
	addu $t3, $t8, $zero
	la $a0, g_dqr3($zero)
	li $v0, 4
	syscall
	la $t8, -44($sp)
	addu $t4, $t8, $zero
	la $t8, -24($sp)
	addu $t5, $t8, $zero
	sw $t3, -52($sp)
	sw $t2, -56($sp)
	sw $t4, -60($sp)
	sw $t1, -64($sp)
	sw $t0, -68($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -76
	addu $a0, $t5, $zero
	li $a1, 4
	jal func_getIndex
	addi $sp, $sp, 76
	lw $t0, -68($sp)
	lw $t1, -64($sp)
	lw $t4, -60($sp)
	lw $t2, -56($sp)
	lw $t3, -52($sp)
	addu $t5, $v0, $zero
	addiu $t5, $t5, 4
	sw $t3, -52($sp)
	sw $t2, -56($sp)
	sw $t1, -64($sp)
	sw $t0, -68($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -80
	addu $a0, $t4, $zero
	li $a1, 4
	addu $a2, $t5, $zero
	jal func_setIndex
	addi $sp, $sp, 80
	lw $t0, -68($sp)
	lw $t1, -64($sp)
	lw $t2, -56($sp)
	lw $t3, -52($sp)
	addu $t4, $v0, $zero
	addu $a0, $t4, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr4($zero)
	addu $t4, $t8, $zero
	la $a0, g_dqr4($zero)
	li $v0, 4
	syscall
	la $t8, -44($sp)
	addu $t5, $t8, $zero
	sw $t4, -48($sp)
	sw $t3, -52($sp)
	sw $t2, -60($sp)
	sw $t1, -64($sp)
	sw $t0, -68($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -76
	addu $a0, $t5, $zero
	li $a1, 0
	jal func_getIndex
	addi $sp, $sp, 76
	lw $t0, -68($sp)
	lw $t1, -64($sp)
	lw $t2, -60($sp)
	lw $t3, -52($sp)
	lw $t4, -48($sp)
	addu $t5, $v0, $zero
	addu $a0, $t5, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr5($zero)
	addu $t5, $t8, $zero
	la $a0, g_dqr5($zero)
	li $v0, 4
	syscall
	la $t8, -44($sp)
	addu $t6, $t8, $zero
	sw $t5, -52($sp)
	sw $t4, -56($sp)
	sw $t3, -60($sp)
	sw $t2, -64($sp)
	sw $t1, -68($sp)
	sw $t0, -72($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -80
	addu $a0, $t6, $zero
	li $a1, 1
	jal func_getIndex
	addi $sp, $sp, 80
	lw $t0, -72($sp)
	lw $t1, -68($sp)
	lw $t2, -64($sp)
	lw $t3, -60($sp)
	lw $t4, -56($sp)
	lw $t5, -52($sp)
	addu $t6, $v0, $zero
	addu $a0, $t6, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr6($zero)
	addu $t6, $t8, $zero
	la $a0, g_dqr6($zero)
	li $v0, 4
	syscall
	la $t8, -44($sp)
	addu $t7, $t8, $zero
	sw $t6, -48($sp)
	sw $t5, -52($sp)
	sw $t4, -56($sp)
	sw $t3, -64($sp)
	sw $t2, -68($sp)
	sw $t1, -72($sp)
	sw $t0, -76($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -84
	addu $a0, $t7, $zero
	li $a1, 2
	jal func_getIndex
	addi $sp, $sp, 84
	lw $t0, -76($sp)
	lw $t1, -72($sp)
	lw $t2, -68($sp)
	lw $t3, -64($sp)
	lw $t4, -56($sp)
	lw $t5, -52($sp)
	lw $t6, -48($sp)
	addu $t7, $v0, $zero
	addu $a0, $t7, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr7($zero)
	addu $t7, $t8, $zero
	la $a0, g_dqr7($zero)
	li $v0, 4
	syscall
	la $t8, -44($sp)
	addu $s0, $t8, $zero
	sw $t7, -52($sp)
	sw $t6, -56($sp)
	sw $t5, -60($sp)
	sw $t4, -64($sp)
	sw $t3, -68($sp)
	sw $t2, -72($sp)
	sw $t1, -76($sp)
	sw $t0, -80($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -88
	addu $a0, $s0, $zero
	li $a1, 3
	jal func_getIndex
	addi $sp, $sp, 88
	lw $t0, -80($sp)
	lw $t1, -76($sp)
	lw $t2, -72($sp)
	lw $t3, -68($sp)
	lw $t4, -64($sp)
	lw $t5, -60($sp)
	lw $t6, -56($sp)
	lw $t7, -52($sp)
	addu $s0, $v0, $zero
	addu $a0, $s0, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr8($zero)
	addu $s0, $t8, $zero
	la $a0, g_dqr8($zero)
	li $v0, 4
	syscall
	la $t8, -44($sp)
	addu $s1, $t8, $zero
	sw $s0, -48($sp)
	sw $t7, -52($sp)
	sw $t6, -56($sp)
	sw $t5, -60($sp)
	sw $t4, -68($sp)
	sw $t3, -72($sp)
	sw $t2, -76($sp)
	sw $t1, -80($sp)
	sw $t0, -84($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -92
	addu $a0, $s1, $zero
	li $a1, 4
	jal func_getIndex
	addi $sp, $sp, 92
	lw $t0, -84($sp)
	lw $t1, -80($sp)
	lw $t2, -76($sp)
	lw $t3, -72($sp)
	lw $t4, -68($sp)
	lw $t5, -60($sp)
	lw $t6, -56($sp)
	lw $t7, -52($sp)
	lw $s0, -48($sp)
	addu $s1, $v0, $zero
	addu $a0, $s1, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr9($zero)
	addu $s1, $t8, $zero
	la $a0, g_dqr9($zero)
	li $v0, 4
	syscall
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
