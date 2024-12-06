.data
	g_dqr0: .asciiz "21371295"


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
	li $t8, 0
	sw $t8, -12($sp)
	lw $t8, -12($sp)
	sw $t8, -16($sp)
	lw $t8, -16($sp)
	sgt $v1, $t8, 0
	sw $v1, -20($sp)
	lw $t8, -20($sp)
	beq $t8, $zero, func_main_block_6
	j func_main_block_5
func_main_block_5:
	li $t8, 1
	sw $t8, -12($sp)
	j func_main_block_7
func_main_block_6:
	li $t8, 0
	sw $t8, -12($sp)
	j func_main_block_7
func_main_block_7:
	li $t8, 1
	sw $t8, -24($sp)
	li $t8, 2
	sw $t8, -28($sp)
	lw $t8, -24($sp)
	sw $t8, -32($sp)
	lw $t8, -32($sp)
	sge $v1, $t8, 0
	sw $v1, -36($sp)
	lw $t8, -36($sp)
	beq $t8, $zero, func_main_block_13
	j func_main_block_12
func_main_block_12:
	li $t8, 1
	sw $t8, -24($sp)
	j func_main_block_13
func_main_block_13:
	lw $t8, -24($sp)
	sw $t8, -40($sp)
	lw $t8, -40($sp)
	sge $v1, $t8, 0
	sw $v1, -44($sp)
	lw $t8, -44($sp)
	beq $t8, $zero, func_main_block_17
	j func_main_block_16
func_main_block_16:
	j func_main_block_17
func_main_block_17:
	lw $t8, -24($sp)
	sw $t8, -48($sp)
	lw $t8, -48($sp)
	seq $v1, $t8, 0
	sw $v1, -52($sp)
	lw $t8, -52($sp)
	sne $v1, $t8, 0
	sw $v1, -56($sp)
	lw $t8, -56($sp)
	beq $t8, $zero, func_main_block_23
	j func_main_block_22
func_main_block_22:
	j func_main_block_24
func_main_block_23:
	j func_main_block_24
func_main_block_24:
	lw $t8, -28($sp)
	sw $t8, -60($sp)
	lw $t8, -60($sp)
	sle $v1, $t8, 0
	sw $v1, -64($sp)
	lw $t8, -64($sp)
	beq $t8, $zero, func_main_block_28
	j func_main_block_27
func_main_block_27:
	li $t8, 2
	sw $t8, -28($sp)
	j func_main_block_28
func_main_block_28:
	lw $t8, -24($sp)
	sw $t8, -68($sp)
	lw $t8, -28($sp)
	sw $t8, -72($sp)
	lw $t8, -68($sp)
	lw $t9, -72($sp)
	seq $v1, $t8, $t9
	sw $v1, -76($sp)
	lw $t8, -76($sp)
	beq $t8, $zero, func_main_block_33
	j func_main_block_32
func_main_block_32:
	li $t8, 1
	sw $t8, -12($sp)
	j func_main_block_33
func_main_block_33:
	lw $t8, -24($sp)
	sw $t8, -80($sp)
	lw $t8, -28($sp)
	sw $t8, -84($sp)
	lw $t8, -80($sp)
	lw $t9, -84($sp)
	sne $v1, $t8, $t9
	sw $v1, -88($sp)
	lw $t8, -88($sp)
	beq $t8, $zero, func_main_block_38
	j func_main_block_37
func_main_block_37:
	li $t8, 0
	sw $t8, -12($sp)
	j func_main_block_38
func_main_block_38:
	lw $t8, -24($sp)
	sw $t8, -92($sp)
	lw $t8, -28($sp)
	sw $t8, -96($sp)
	lw $t8, -92($sp)
	lw $t9, -96($sp)
	sne $v1, $t8, $t9
	sw $v1, -100($sp)
	lw $t8, -100($sp)
	beq $t8, $zero, func_main_block_46
	j func_main_block_42
func_main_block_42:
	lw $t8, -24($sp)
	sw $t8, -104($sp)
	lw $t8, -104($sp)
	sgt $v1, $t8, 0
	sw $v1, -108($sp)
	lw $t8, -108($sp)
	beq $t8, $zero, func_main_block_46
	j func_main_block_45
func_main_block_45:
	li $t8, 1
	sw $t8, -12($sp)
	j func_main_block_46
func_main_block_46:
	lw $t8, -24($sp)
	sw $t8, -112($sp)
	lw $t8, -28($sp)
	sw $t8, -116($sp)
	lw $t8, -112($sp)
	lw $t9, -116($sp)
	sne $v1, $t8, $t9
	sw $v1, -120($sp)
	lw $t8, -120($sp)
	beq $t8, $zero, func_main_block_50
	j func_main_block_53
func_main_block_50:
	lw $t8, -24($sp)
	sw $t8, -124($sp)
	lw $t8, -124($sp)
	sgt $v1, $t8, 0
	sw $v1, -128($sp)
	lw $t8, -128($sp)
	beq $t8, $zero, func_main_block_54
	j func_main_block_53
func_main_block_53:
	li $t8, 2
	sw $t8, -12($sp)
	j func_main_block_54
func_main_block_54:
	lw $t8, -24($sp)
	sw $t8, -132($sp)
	lw $t8, -132($sp)
	addiu $v1, $t8, 1
	sw $v1, -136($sp)
	lw $t8, -136($sp)
	sw $t8, -24($sp)
	li $t8, 2
	sw $t8, -24($sp)
	li $t8, -1
	sw $t8, -24($sp)
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
