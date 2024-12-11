.data
	g_pos_r: .word 0:500
	g_pos_e: .word 0:500
	g_s: .asciiz "RexloveStudybutstudyemmmrx"


.text
	jal func_main
	li $v0, 10
	syscall

func_main:
	sw $ra, -4($sp)
func_main_block_0:
	li $v0, 5
	syscall
	addu $t0, $v0, $zero
	sw $t0, -8($sp)
	li $t8, 0
	sw $t8, -16($sp)
	li $t8, 0
	sw $t8, -20($sp)
	li $t8, 0
	sw $t8, -24($sp)
	li $t8, 0
	sw $t8, -28($sp)
	li $t8, 0
	sw $t8, -32($sp)
	li $t8, 0
	sw $t8, -36($sp)
	li $t8, 0
	sw $t8, -12($sp)
	j func_main_block_10
func_main_block_10:
	lw $t0, -12($sp)
	lw $t1, -8($sp)
	slt $t0, $t0, $t1
	beq $t0, $zero, func_main_block_86
	j func_main_block_14
func_main_block_14:
	lw $t0, -12($sp)
	la $t8, g_s($zero)
	sll $t0, $t0, 0
	addu $t8, $t8, $t0
	addu $t0, $t8, $zero
	lbu $t1, 0($t0)
	seq $t0, $t1, 82
	beq $t0, $zero, func_main_block_20
	j func_main_block_26
func_main_block_20:
	lw $t0, -12($sp)
	la $t8, g_s($zero)
	sll $t0, $t0, 0
	addu $t8, $t8, $t0
	addu $t0, $t8, $zero
	lbu $t1, 0($t0)
	seq $t0, $t1, 114
	beq $t0, $zero, func_main_block_31
	j func_main_block_26
func_main_block_26:
	lw $t0, -16($sp)
	la $t8, g_pos_r($zero)
	sll $t0, $t0, 2
	addu $t8, $t8, $t0
	addu $t0, $t8, $zero
	lw $t1, -12($sp)
	sw $t1, 0($t0)
	lw $t0, -20($sp)
	j func_main_block_31
func_main_block_31:
	lw $t0, -12($sp)
	la $t8, g_s($zero)
	sll $t0, $t0, 0
	addu $t8, $t8, $t0
	addu $t0, $t8, $zero
	lbu $t1, 0($t0)
	seq $t0, $t1, 101
	beq $t0, $zero, func_main_block_37
	j func_main_block_43
func_main_block_37:
	lw $t0, -12($sp)
	la $t8, g_s($zero)
	sll $t0, $t0, 0
	addu $t8, $t8, $t0
	addu $t0, $t8, $zero
	lbu $t1, 0($t0)
	seq $t0, $t1, 69
	beq $t0, $zero, func_main_block_44
	j func_main_block_43
func_main_block_43:
	j func_main_block_44
func_main_block_44:
	lw $t0, -20($sp)
	lw $t1, -28($sp)
	lw $t2, -24($sp)
	la $t8, g_pos_e($zero)
	sll $t2, $t2, 2
	addu $t8, $t8, $t2
	addu $t2, $t8, $zero
	lw $t3, -12($sp)
	sw $t3, 0($t2)
	lw $t2, -28($sp)
	lw $t3, -12($sp)
	la $t8, g_s($zero)
	sll $t3, $t3, 0
	addu $t8, $t8, $t3
	addu $t3, $t8, $zero
	lbu $t4, 0($t3)
	seq $t3, $t4, 120
	beq $t3, $zero, func_main_block_56
	j func_main_block_62
func_main_block_56:
	lw $t0, -12($sp)
	la $t8, g_s($zero)
	sll $t0, $t0, 0
	addu $t8, $t8, $t0
	addu $t0, $t8, $zero
	lbu $t1, 0($t0)
	seq $t0, $t1, 88
	beq $t0, $zero, func_main_block_82
	j func_main_block_62
func_main_block_62:
	lw $t0, -20($sp)
	sne $t0, $t0, 0
	beq $t0, $zero, func_main_block_81
	j func_main_block_65
func_main_block_65:
	lw $t0, -28($sp)
	sne $t0, $t0, 0
	beq $t0, $zero, func_main_block_81
	j func_main_block_68
func_main_block_68:
	lw $t0, -32($sp)
	la $t8, g_pos_r($zero)
	sll $t0, $t0, 2
	addu $t8, $t8, $t0
	addu $t0, $t8, $zero
	lw $t1, 0($t0)
	la $t8, g_s($zero)
	sll $t1, $t1, 0
	addu $t8, $t8, $t1
	addu $t0, $t8, $zero
	li $t8, 0
	sb $t8, 0($t0)
	lw $t0, -20($sp)
	lw $t1, -36($sp)
	la $t8, g_pos_e($zero)
	sll $t1, $t1, 2
	addu $t8, $t8, $t1
	addu $t1, $t8, $zero
	lw $t2, 0($t1)
	la $t8, g_s($zero)
	sll $t2, $t2, 0
	addu $t8, $t8, $t2
	addu $t1, $t8, $zero
	li $t8, 0
	sb $t8, 0($t1)
	lw $t1, -28($sp)
	lw $t2, -12($sp)
	la $t8, g_s($zero)
	sll $t2, $t2, 0
	addu $t8, $t8, $t2
	addu $t2, $t8, $zero
	li $t8, 0
	sb $t8, 0($t2)
	j func_main_block_81
func_main_block_81:
	j func_main_block_82
func_main_block_82:
	j func_main_block_83
func_main_block_83:
	lw $t0, -12($sp)
	addiu $t0, $t0, 1
	sw $t0, -12($sp)
	j func_main_block_10
func_main_block_86:
	li $t8, 0
	sw $t8, -12($sp)
	j func_main_block_87
func_main_block_87:
	lw $t0, -12($sp)
	lw $t1, -8($sp)
	slt $t0, $t0, $t1
	beq $t0, $zero, func_main_block_106
	j func_main_block_91
func_main_block_91:
	lw $t0, -12($sp)
	la $t8, g_s($zero)
	sll $t0, $t0, 0
	addu $t8, $t8, $t0
	addu $t0, $t8, $zero
	lbu $t1, 0($t0)
	sne $t0, $t1, 0
	beq $t0, $zero, func_main_block_102
	j func_main_block_97
func_main_block_97:
	lw $t0, -12($sp)
	la $t8, g_s($zero)
	sll $t0, $t0, 0
	addu $t8, $t8, $t0
	addu $t0, $t8, $zero
	lbu $t1, 0($t0)
	addu $a0, $t1, $zero
	li $v0, 11
	syscall
	j func_main_block_102
func_main_block_102:
	j func_main_block_103
func_main_block_103:
	lw $t0, -12($sp)
	addiu $t0, $t0, 1
	sw $t0, -12($sp)
	j func_main_block_87
func_main_block_106:
