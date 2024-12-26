.data
	g_next: .word 0:10000
	g_prev: .word 0:10000
	g_dqr0: .asciiz "formula:  "
	g_dqr1: .asciiz "\n"
	g_dqr2: .asciiz "simulate: "
	g_dqr3: .asciiz "\n"


.text
	jal func_main
	li $v0, 10
	syscall

func_simulate:
	sw $ra, -4($sp)
func_simulate_block_2:
	sw $a0, -8($sp)
	sw $a1, -12($sp)
	li $t8, 1
	sw $t8, -24($sp)
	j func_simulate_block_6
func_simulate_block_6:
	lw $t0, -24($sp)
	lw $t1, -8($sp)
	slt $t2, $t0, $t1
	beq $t2, $zero, func_simulate_block_22
	j func_simulate_block_10
func_simulate_block_10:
	lw $t0, -24($sp)
	la $t8, g_next($zero)
	sll $t0, $t0, 2
	addu $t8, $t8, $t0
	addu $t1, $t8, $zero
	lw $t2, -24($sp)
	addiu $t3, $t2, 1
	sw $t3, 0($t1)
	lw $t4, -24($sp)
	addiu $t5, $t4, 1
	la $t8, g_prev($zero)
	sll $t5, $t5, 2
	addu $t8, $t8, $t5
	addu $t6, $t8, $zero
	lw $t7, -24($sp)
	sw $t7, 0($t6)
	j func_simulate_block_19
func_simulate_block_19:
	lw $t0, -24($sp)
	addiu $t1, $t0, 1
	sw $t1, -24($sp)
	j func_simulate_block_6
func_simulate_block_22:
	lw $t0, -8($sp)
	la $t8, g_next($zero)
	sll $t0, $t0, 2
	addu $t8, $t8, $t0
	addu $t1, $t8, $zero
	li $t8, 1
	sw $t8, 0($t1)
	la $t8, g_prev($zero)
	addiu $t8, $t8, 4
	addu $t2, $t8, $zero
	lw $t3, -8($sp)
	sw $t3, 0($t2)
	li $t8, 1
	sw $t8, -28($sp)
	li $t8, 1
	sw $t8, -24($sp)
	j func_simulate_block_29
func_simulate_block_29:
	lw $t0, -24($sp)
	lw $t1, -8($sp)
	slt $t2, $t0, $t1
	beq $t2, $zero, func_simulate_block_66
	j func_simulate_block_33
func_simulate_block_33:
	li $t8, 1
	sw $t8, -32($sp)
	j func_simulate_block_34
func_simulate_block_34:
	lw $t0, -32($sp)
	lw $t1, -12($sp)
	slt $t2, $t0, $t1
	beq $t2, $zero, func_simulate_block_45
	j func_simulate_block_38
func_simulate_block_38:
	lw $t0, -28($sp)
	la $t8, g_next($zero)
	sll $t0, $t0, 2
	addu $t8, $t8, $t0
	addu $t1, $t8, $zero
	lw $t2, 0($t1)
	sw $t2, -28($sp)
	j func_simulate_block_42
func_simulate_block_42:
	lw $t0, -32($sp)
	addiu $t1, $t0, 1
	sw $t1, -32($sp)
	j func_simulate_block_34
func_simulate_block_45:
	lw $t0, -28($sp)
	la $t8, g_next($zero)
	sll $t0, $t0, 2
	addu $t8, $t8, $t0
	addu $t1, $t8, $zero
	lw $t2, 0($t1)
	la $t8, g_prev($zero)
	sll $t2, $t2, 2
	addu $t8, $t8, $t2
	addu $t3, $t8, $zero
	lw $t4, -28($sp)
	la $t8, g_prev($zero)
	sll $t4, $t4, 2
	addu $t8, $t8, $t4
	addu $t5, $t8, $zero
	lw $t6, 0($t5)
	sw $t6, 0($t3)
	lw $t7, -28($sp)
	la $t8, g_prev($zero)
	sll $t7, $t7, 2
	addu $t8, $t8, $t7
	addu $s0, $t8, $zero
	lw $s1, 0($s0)
	la $t8, g_next($zero)
	sll $s1, $s1, 2
	addu $t8, $t8, $s1
	addu $s2, $t8, $zero
	lw $s3, -28($sp)
	la $t8, g_next($zero)
	sll $s3, $s3, 2
	addu $t8, $t8, $s3
	addu $s4, $t8, $zero
	lw $s5, 0($s4)
	sw $s5, 0($s2)
	lw $s6, -28($sp)
	la $t8, g_next($zero)
	sll $s6, $s6, 2
	addu $t8, $t8, $s6
	addu $s7, $t8, $zero
	lw $v1, 0($s7)
	sw $v1, -36($sp)
	lw $t8, -36($sp)
	sw $t8, -28($sp)
	j func_simulate_block_63
func_simulate_block_63:
	lw $t0, -24($sp)
	addiu $t1, $t0, 1
	sw $t1, -24($sp)
	j func_simulate_block_29
func_simulate_block_66:
	lw $t0, -28($sp)
	addu $v0, $t0, $zero
	lw $ra, -4($sp)
	jr $ra
func_f:
	sw $ra, -4($sp)
func_f_block_2:
	sw $a0, -8($sp)
	sw $a1, -12($sp)
	lw $t0, -8($sp)
	seq $t1, $t0, 1
	beq $t1, $zero, func_f_block_9
	j func_f_block_7
func_f_block_7:
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
func_f_block_8:
	j func_f_block_9
func_f_block_9:
	lw $t0, -12($sp)
	lw $t1, -8($sp)
	rem $t2, $t0, $t1
	addiu $t3, $t2, -1
	sw $t3, -24($sp)
	lw $t4, -8($sp)
	addiu $t5, $t4, -1
	lw $t6, -12($sp)
	sw $t4, -40($sp)
	sw $t3, -44($sp)
	sw $t2, -48($sp)
	sw $t1, -52($sp)
	sw $t0, -56($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -64
	addu $a0, $t5, $zero
	addu $a1, $t6, $zero
	jal func_f
	addiu $sp, $sp, 64
	lw $t0, -56($sp)
	lw $t1, -52($sp)
	lw $t2, -48($sp)
	lw $t3, -44($sp)
	lw $t4, -40($sp)
	lw $t5, -36($sp)
	lw $t6, -32($sp)
	addu $t7, $v0, $zero
	sw $t7, -28($sp)
	lw $s0, -28($sp)
	sge $s1, $s0, 0
	beq $s1, $zero, func_f_block_35
	j func_f_block_22
func_f_block_22:
	lw $t0, -28($sp)
	lw $t1, -8($sp)
	addiu $t2, $t1, -2
	lw $t3, -24($sp)
	subu $t4, $t2, $t3
	sle $t5, $t0, $t4
	beq $t5, $zero, func_f_block_35
	j func_f_block_29
func_f_block_29:
	lw $t0, -28($sp)
	lw $t1, -24($sp)
	addu $t2, $t0, $t1
	addiu $t3, $t2, 1
	addu $v0, $t3, $zero
	lw $ra, -4($sp)
	jr $ra
func_f_block_34:
	j func_f_block_43
func_f_block_35:
	lw $t0, -28($sp)
	lw $t1, -8($sp)
	lw $t2, -24($sp)
	subu $t3, $t1, $t2
	addiu $t4, $t3, -1
	subu $t5, $t0, $t4
	addu $v0, $t5, $zero
	lw $ra, -4($sp)
	jr $ra
func_f_block_42:
	j func_f_block_43
func_f_block_43:
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
func_main:
	sw $ra, -4($sp)
func_main_block_0:
	li $v0, 5
	syscall
	addu $t0, $v0, $zero
	sw $t0, -8($sp)
	li $t8, 0
	sw $t8, -20($sp)
	j func_main_block_6
func_main_block_6:
	lw $t0, -20($sp)
	lw $t1, -8($sp)
	slt $t2, $t0, $t1
	beq $t2, $zero, func_main_block_27
	j func_main_block_10
func_main_block_10:
	li $v0, 5
	syscall
	addu $t0, $v0, $zero
	sw $t0, -12($sp)
	li $v0, 5
	syscall
	addu $t1, $v0, $zero
	sw $t1, -16($sp)
	lw $t2, -12($sp)
	lw $t3, -16($sp)
	sw $t1, -32($sp)
	sw $t0, -36($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -44
	addu $a0, $t2, $zero
	addu $a1, $t3, $zero
	jal func_f
	addiu $sp, $sp, 44
	lw $t0, -36($sp)
	lw $t1, -32($sp)
	lw $t2, -28($sp)
	lw $t3, -24($sp)
	addu $t4, $v0, $zero
	addiu $t5, $t4, 1
	la $t8, g_dqr0($zero)
	addu $t6, $t8, $zero
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	addu $a0, $t5, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr1($zero)
	addu $t7, $t8, $zero
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	lw $s0, -12($sp)
	lw $s1, -16($sp)
	sw $t7, -32($sp)
	sw $t6, -36($sp)
	sw $t5, -40($sp)
	sw $t4, -44($sp)
	sw $t3, -48($sp)
	sw $t2, -52($sp)
	sw $t1, -56($sp)
	sw $t0, -60($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -68
	addu $a0, $s0, $zero
	addu $a1, $s1, $zero
	jal func_simulate
	addiu $sp, $sp, 68
	lw $t0, -60($sp)
	lw $t1, -56($sp)
	lw $t2, -52($sp)
	lw $t3, -48($sp)
	lw $t4, -44($sp)
	lw $t5, -40($sp)
	lw $t6, -36($sp)
	lw $t7, -32($sp)
	lw $s0, -28($sp)
	lw $s1, -24($sp)
	addu $s2, $v0, $zero
	la $t8, g_dqr2($zero)
	addu $s3, $t8, $zero
	la $a0, g_dqr2($zero)
	li $v0, 4
	syscall
	addu $a0, $s2, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr3($zero)
	addu $s4, $t8, $zero
	la $a0, g_dqr3($zero)
	li $v0, 4
	syscall
	lw $s5, -20($sp)
	addiu $s6, $s5, 2
	addiu $s7, $s6, -1
	sw $s7, -20($sp)
	j func_main_block_6
func_main_block_27:
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
