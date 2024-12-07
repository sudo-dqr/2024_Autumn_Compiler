.data
	g_chArr: .byte 0:100
	g_dqr0: .asciiz "\n"
	g_dqr1: .asciiz "\n"


.text
	jal func_main
	li $v0, 10
	syscall

func_charAtIndex:
	sw $ra, -4($sp)
func_charAtIndex_block_2:
	sw $a0, -8($sp)
	sw $a1, -12($sp)
	lw $t8, -8($sp)
	sw $t8, -24($sp)
	lw $t8, -12($sp)
	sw $t8, -28($sp)
	lw $t8, -24($sp)
	lw $t9, -28($sp)
	mul $t9, $t9, 1
	addu $t8, $t8, $t9
	sw $t8, -32($sp)
	lw $t8, -32($sp)
	lbu $t8, 0($t8)
	sw $t8, -36($sp)
	lw $v0, -36($sp)
	lw $ra, -4($sp)
	jr $ra
func_main:
	sw $ra, -4($sp)
func_main_block_0:
	li $t8, 0
	sw $t8, -8($sp)
	j func_main_block_2
func_main_block_2:
	lw $t8, -8($sp)
	sw $t8, -12($sp)
	lw $t8, -12($sp)
	slti $v1, $t8, 5
	sw $v1, -16($sp)
	lw $t8, -16($sp)
	beq $t8, $zero, func_main_block_14
	j func_main_block_5
func_main_block_5:
	lw $t8, -8($sp)
	sw $t8, -20($sp)
	la $t8, g_chArr($zero)
	lw $t9, -20($sp)
	mul $t9, $t9, 1
	addu $t8, $t8, $t9
	sw $t8, -24($sp)
	lw $t8, -8($sp)
	sw $t8, -28($sp)
	lw $t9, -28($sp)
	addiu $v1, $t9, 65
	sw $v1, -32($sp)
	lw $t8, -32($sp)
	lw $t9, -24($sp)
	sb $t8, 0($t9)
	j func_main_block_11
func_main_block_11:
	lw $t8, -8($sp)
	sw $t8, -36($sp)
	lw $t8, -36($sp)
	addiu $v1, $t8, 1
	sw $v1, -40($sp)
	lw $t8, -40($sp)
	sw $t8, -8($sp)
	j func_main_block_2
func_main_block_14:
	la $t8, g_chArr($zero)
	addiu $t8, $t8, 4
	sw $t8, -44($sp)
	lw $t8, -44($sp)
	lbu $t8, 0($t8)
	sw $t8, -48($sp)
	lw $a0, -48($sp)
	li $v0, 11
	syscall
	la $t8, g_dqr0($zero)
	sw $t8, -52($sp)
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	la $t8, g_chArr($zero)
	sw $t8, -56($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -64
	lw $a0, -56($fp)
	li $a1, 4
	jal func_charAtIndex
	addi $sp, $sp, 64
	sw $v0, -60($sp)
	lw $a0, -60($sp)
	li $v0, 11
	syscall
	la $t8, g_dqr1($zero)
	sw $t8, -64($sp)
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
