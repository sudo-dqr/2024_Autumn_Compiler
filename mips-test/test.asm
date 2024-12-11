.data
	g_dqr0: .asciiz "!1 should be 0: Correct\n"
	g_dqr1: .asciiz "!1 should be 0: Incorrect\n"
	g_dqr2: .asciiz "!0 should be 1: Correct\n"
	g_dqr3: .asciiz "!0 should be 1: Incorrect\n"
	g_dqr4: .asciiz "good job correct answer\n"
	g_dqr5: .asciiz "failed\n"
	g_dqr6: .asciiz "!5 should be 0: Correct\n"
	g_dqr7: .asciiz "!5 should be 0: Incorrect\n"
	g_dqr8: .asciiz "!0 should be 1: Correct\n"
	g_dqr9: .asciiz "!0 should be 1: Incorrect\n"


.text
	jal func_main
	li $v0, 10
	syscall

func_main:
	sw $ra, -4($sp)
func_main_block_0:
	li $t8, 1
	sw $t8, -8($sp)
	li $t8, 0
	sw $t8, -12($sp)
	lw $t0, -8($sp)
	seq $t0, $t0, 0
	seq $t0, $t0, 0
	beq $t0, $zero, func_main_block_9
	j func_main_block_7
func_main_block_7:
	la $t8, g_dqr0($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	j func_main_block_11
func_main_block_9:
	la $t8, g_dqr1($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	j func_main_block_11
func_main_block_11:
	lw $t0, -12($sp)
	seq $t0, $t0, 0
	seq $t0, $t0, 1
	beq $t0, $zero, func_main_block_18
	j func_main_block_16
func_main_block_16:
	la $t8, g_dqr2($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr2($zero)
	li $v0, 4
	syscall
	j func_main_block_20
func_main_block_18:
	la $t8, g_dqr3($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr3($zero)
	li $v0, 4
	syscall
	j func_main_block_20
func_main_block_20:
	li $t8, 5
	sb $t8, -16($sp)
	li $t8, 0
	sb $t8, -20($sp)
	lbu $t0, -20($sp)
	seq $t0, $t0, 0
	sne $t0, $t0, 0
	beq $t0, $zero, func_main_block_30
	j func_main_block_28
func_main_block_28:
	la $t8, g_dqr4($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr4($zero)
	li $v0, 4
	syscall
	j func_main_block_32
func_main_block_30:
	la $t8, g_dqr5($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr5($zero)
	li $v0, 4
	syscall
	j func_main_block_32
func_main_block_32:
	lbu $t0, -16($sp)
	seq $t0, $t0, 0
	seq $t0, $t0, 0
	beq $t0, $zero, func_main_block_40
	j func_main_block_38
func_main_block_38:
	la $t8, g_dqr6($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr6($zero)
	li $v0, 4
	syscall
	j func_main_block_42
func_main_block_40:
	la $t8, g_dqr7($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr7($zero)
	li $v0, 4
	syscall
	j func_main_block_42
func_main_block_42:
	lbu $t0, -20($sp)
	seq $t0, $t0, 0
	seq $t0, $t0, 1
	beq $t0, $zero, func_main_block_50
	j func_main_block_48
func_main_block_48:
	la $t8, g_dqr8($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr8($zero)
	li $v0, 4
	syscall
	j func_main_block_52
func_main_block_50:
	la $t8, g_dqr9($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr9($zero)
	li $v0, 4
	syscall
	j func_main_block_52
func_main_block_52:
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
