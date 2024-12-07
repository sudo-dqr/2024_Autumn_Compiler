.data
	g_dqr0: .asciiz "->"
	g_dqr1: .asciiz "\n"
	g_dqr2: .asciiz "21371119\n"
	g_dqr3: .asciiz "fun1:\n"


.text
	jal func_main
	li $v0, 10
	syscall

func_move:
	sw $ra, -4($sp)
func_move_block_2:
	sw $a0, -8($sp)
	sw $a1, -12($sp)
	lw $t8, -8($sp)
	sw $t8, -24($sp)
	lw $t8, -12($sp)
	sw $t8, -28($sp)
	lw $a0, -24($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr0($zero)
	sw $t8, -32($sp)
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	lw $a0, -28($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr1($zero)
	sw $t8, -36($sp)
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	lw $ra, -4($sp)
	jr $ra
func_hanoi:
	sw $ra, -4($sp)
func_hanoi_block_4:
	sw $a0, -8($sp)
	sw $a1, -12($sp)
	sw $a2, -16($sp)
	sw $a3, -20($sp)
	lw $t8, -8($sp)
	sw $t8, -40($sp)
	lw $t8, -40($sp)
	seq $v1, $t8, 1
	sw $v1, -44($sp)
	lw $t8, -44($sp)
	beq $t8, $zero, func_hanoi_block_14
	j func_hanoi_block_11
func_hanoi_block_11:
	lw $t8, -12($sp)
	sw $t8, -48($sp)
	lw $t8, -20($sp)
	sw $t8, -52($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -60
	lw $a0, -48($fp)
	lw $a1, -52($fp)
	jal func_move
	addi $sp, $sp, 60
	sw $v0, -56($sp)
	j func_hanoi_block_27
func_hanoi_block_14:
	lw $t8, -8($sp)
	sw $t8, -60($sp)
	lw $t8, -60($sp)
	subu $v1, $t8, 1
	sw $v1, -64($sp)
	lw $t8, -12($sp)
	sw $t8, -68($sp)
	lw $t8, -20($sp)
	sw $t8, -72($sp)
	lw $t8, -16($sp)
	sw $t8, -76($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -92
	lw $a0, -64($fp)
	lw $a1, -68($fp)
	lw $a2, -72($fp)
	lw $a3, -76($fp)
	jal func_hanoi
	addi $sp, $sp, 92
	sw $v0, -80($sp)
	lw $t8, -12($sp)
	sw $t8, -84($sp)
	lw $t8, -20($sp)
	sw $t8, -88($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -96
	lw $a0, -84($fp)
	lw $a1, -88($fp)
	jal func_move
	addi $sp, $sp, 96
	sw $v0, -92($sp)
	lw $t8, -8($sp)
	sw $t8, -96($sp)
	lw $t8, -96($sp)
	subu $v1, $t8, 1
	sw $v1, -100($sp)
	lw $t8, -16($sp)
	sw $t8, -104($sp)
	lw $t8, -12($sp)
	sw $t8, -108($sp)
	lw $t8, -20($sp)
	sw $t8, -112($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -128
	lw $a0, -100($fp)
	lw $a1, -104($fp)
	lw $a2, -108($fp)
	lw $a3, -112($fp)
	jal func_hanoi
	addi $sp, $sp, 128
	sw $v0, -116($sp)
	j func_hanoi_block_27
func_hanoi_block_27:
	lw $ra, -4($sp)
	jr $ra
func_main:
	sw $ra, -4($sp)
func_main_block_0:
	li $t8, 0
	sw $t8, -8($sp)
	li $v0, 5
	syscall
	sw $v0, -12($sp)
	lw $t8, -12($sp)
	sw $t8, -8($sp)
	la $t8, g_dqr2($zero)
	sw $t8, -16($sp)
	la $a0, g_dqr2($zero)
	li $v0, 4
	syscall
	lw $t8, -8($sp)
	sw $t8, -20($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -36
	lw $a0, -20($fp)
	li $a1, 1
	li $a2, 2
	li $a3, 3
	jal func_hanoi
	addi $sp, $sp, 36
	sw $v0, -24($sp)
	li $t8, 0
	sw $t8, -28($sp)
	lw $t8, -28($sp)
	sw $t8, -32($sp)
	la $t8, g_dqr3($zero)
	sw $t8, -36($sp)
	la $a0, g_dqr3($zero)
	li $v0, 4
	syscall
	lw $a0, -32($sp)
	li $v0, 1
	syscall
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
