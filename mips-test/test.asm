.data
	g_constD: .word 1, 2, 3, 4, 5
	g_a1: .byte 97
	g_a2: .byte 98
	g_a3: .byte 99
	g_a4: .asciiz "abcde"
	g_dqr0: .asciiz "\n"
	g_dqr1: .asciiz "\n"
	g_dqr2: .asciiz "\n"
	g_dqr3: .asciiz "\n"
	g_dqr4: .asciiz "\n"
	g_dqr5: .asciiz "\n"
	g_dqr6: .asciiz "\n"
	g_dqr7: .asciiz "22372468\n"
	g_dqr8: .asciiz "\n"
	g_dqr9: .asciiz "\n"


.text
	jal func_main
	li $v0, 10
	syscall

func_funcA:
	sw $ra, -4($sp)
func_funcA_block_0:
	lw $ra, -4($sp)
	jr $ra
func_funcB:
	sw $ra, -4($sp)
func_funcB_block_0:
	li $t8, 0
	sw $t8, -8($sp)
	li $t8, 0
	sw $t8, -12($sp)
	li $t8, 0
	sw $t8, -12($sp)
	j func_funcB_block_3
func_funcB_block_3:
	lw $t8, -12($sp)
	sw $t8, -16($sp)
	lw $t8, -16($sp)
	slti $v1, $t8, 5
	sw $v1, -20($sp)
	lw $t8, -20($sp)
	beq $t8, $zero, func_funcB_block_13
	j func_funcB_block_6
func_funcB_block_6:
	lw $t8, -8($sp)
	sw $t8, -24($sp)
	lw $t8, -12($sp)
	sw $t8, -28($sp)
	lw $t8, -24($sp)
	lw $t9, -28($sp)
	addu $v1, $t8, $t9
	sw $v1, -32($sp)
	lw $t8, -32($sp)
	sw $t8, -8($sp)
	j func_funcB_block_10
func_funcB_block_10:
	lw $t8, -12($sp)
	sw $t8, -36($sp)
	lw $t8, -36($sp)
	addiu $v1, $t8, 1
	sw $v1, -40($sp)
	lw $t8, -40($sp)
	sw $t8, -12($sp)
	j func_funcB_block_3
func_funcB_block_13:
	lw $t8, -8($sp)
	sw $t8, -44($sp)
	lw $a0, -44($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr0($zero)
	sw $t8, -48($sp)
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	li $t8, 0
	sw $t8, -12($sp)
	j func_funcB_block_16
func_funcB_block_16:
	lw $t8, -12($sp)
	sw $t8, -52($sp)
	lw $t8, -52($sp)
	slti $v1, $t8, 5
	sw $v1, -56($sp)
	lw $t8, -56($sp)
	beq $t8, $zero, func_funcB_block_26
	j func_funcB_block_19
func_funcB_block_19:
	lw $t8, -8($sp)
	sw $t8, -60($sp)
	lw $t8, -12($sp)
	sw $t8, -64($sp)
	lw $t8, -60($sp)
	lw $t9, -64($sp)
	addu $v1, $t8, $t9
	sw $v1, -68($sp)
	lw $t8, -68($sp)
	sw $t8, -8($sp)
	j func_funcB_block_23
func_funcB_block_23:
	lw $t8, -12($sp)
	sw $t8, -72($sp)
	lw $t8, -72($sp)
	addiu $v1, $t8, 1
	sw $v1, -76($sp)
	lw $t8, -76($sp)
	sw $t8, -12($sp)
	j func_funcB_block_16
func_funcB_block_26:
	li $t8, 0
	sw $t8, -12($sp)
	j func_funcB_block_27
func_funcB_block_27:
	j func_funcB_block_28
func_funcB_block_28:
	lw $t8, -8($sp)
	sw $t8, -80($sp)
	lw $t8, -12($sp)
	sw $t8, -84($sp)
	lw $t8, -80($sp)
	lw $t9, -84($sp)
	addu $v1, $t8, $t9
	sw $v1, -88($sp)
	lw $t8, -88($sp)
	sw $t8, -8($sp)
	lw $t8, -8($sp)
	sw $t8, -92($sp)
	lw $t8, -92($sp)
	sgt $v1, $t8, 25
	sw $v1, -96($sp)
	lw $t8, -96($sp)
	beq $t8, $zero, func_funcB_block_36
	j func_funcB_block_34
func_funcB_block_34:
	j func_funcB_block_42
func_funcB_block_35:
	j func_funcB_block_38
func_funcB_block_36:
	j func_funcB_block_39
func_funcB_block_37:
	j func_funcB_block_38
func_funcB_block_38:
	j func_funcB_block_39
func_funcB_block_39:
	lw $t8, -12($sp)
	sw $t8, -100($sp)
	lw $t8, -100($sp)
	addiu $v1, $t8, 1
	sw $v1, -104($sp)
	lw $t8, -104($sp)
	sw $t8, -12($sp)
	j func_funcB_block_27
func_funcB_block_42:
	li $t8, 1
	sw $t8, -12($sp)
	j func_funcB_block_43
func_funcB_block_43:
	lw $t8, -12($sp)
	sw $t8, -108($sp)
	lw $t8, -108($sp)
	slti $v1, $t8, 5
	sw $v1, -112($sp)
	lw $t8, -112($sp)
	beq $t8, $zero, func_funcB_block_55
	j func_funcB_block_46
func_funcB_block_46:
	lw $t8, -8($sp)
	sw $t8, -116($sp)
	lw $t8, -12($sp)
	sw $t8, -120($sp)
	lw $t8, -116($sp)
	lw $t9, -120($sp)
	addu $v1, $t8, $t9
	sw $v1, -124($sp)
	lw $t8, -124($sp)
	sw $t8, -8($sp)
	lw $t8, -8($sp)
	sw $t8, -128($sp)
	lw $t8, -128($sp)
	sgt $v1, $t8, 30
	sw $v1, -132($sp)
	lw $t8, -132($sp)
	beq $t8, $zero, func_funcB_block_54
	j func_funcB_block_52
func_funcB_block_52:
	j func_funcB_block_55
func_funcB_block_53:
	j func_funcB_block_54
func_funcB_block_54:
	j func_funcB_block_43
func_funcB_block_55:
	lw $t8, -8($sp)
	sw $t8, -136($sp)
	lw $a0, -136($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr1($zero)
	sw $t8, -140($sp)
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	li $t8, 0
	sw $t8, -12($sp)
	j func_funcB_block_58
func_funcB_block_58:
	j func_funcB_block_59
func_funcB_block_59:
	lw $t8, -8($sp)
	sw $t8, -144($sp)
	lw $t8, -12($sp)
	sw $t8, -148($sp)
	lw $t8, -144($sp)
	lw $t9, -148($sp)
	addu $v1, $t8, $t9
	sw $v1, -152($sp)
	lw $t8, -152($sp)
	sw $t8, -8($sp)
	lw $t8, -8($sp)
	sw $t8, -156($sp)
	lw $t8, -156($sp)
	sgt $v1, $t8, 35
	sw $v1, -160($sp)
	lw $t8, -160($sp)
	beq $t8, $zero, func_funcB_block_67
	j func_funcB_block_65
func_funcB_block_65:
	j func_funcB_block_71
func_funcB_block_66:
	j func_funcB_block_67
func_funcB_block_67:
	j func_funcB_block_68
func_funcB_block_68:
	lw $t8, -12($sp)
	sw $t8, -164($sp)
	lw $t8, -164($sp)
	addiu $v1, $t8, 1
	sw $v1, -168($sp)
	lw $t8, -168($sp)
	sw $t8, -12($sp)
	j func_funcB_block_58
func_funcB_block_71:
	j func_funcB_block_72
func_funcB_block_72:
	lw $t8, -12($sp)
	sw $t8, -172($sp)
	lw $t8, -172($sp)
	slti $v1, $t8, 5
	sw $v1, -176($sp)
	lw $t8, -176($sp)
	beq $t8, $zero, func_funcB_block_83
	j func_funcB_block_75
func_funcB_block_75:
	lw $t8, -8($sp)
	sw $t8, -180($sp)
	lw $t8, -180($sp)
	addiu $v1, $t8, 1
	sw $v1, -184($sp)
	lw $t8, -184($sp)
	sw $t8, -8($sp)
	lw $t8, -8($sp)
	sw $t8, -188($sp)
	lw $t8, -188($sp)
	sgt $v1, $t8, 40
	sw $v1, -192($sp)
	lw $t8, -192($sp)
	beq $t8, $zero, func_funcB_block_82
	j func_funcB_block_80
func_funcB_block_80:
	j func_funcB_block_83
func_funcB_block_81:
	j func_funcB_block_82
func_funcB_block_82:
	j func_funcB_block_72
func_funcB_block_83:
	li $t8, 1
	sw $t8, -12($sp)
	j func_funcB_block_84
func_funcB_block_84:
	j func_funcB_block_85
func_funcB_block_85:
	lw $t8, -8($sp)
	sw $t8, -196($sp)
	lw $t8, -12($sp)
	sw $t8, -200($sp)
	lw $t8, -196($sp)
	lw $t9, -200($sp)
	addu $v1, $t8, $t9
	sw $v1, -204($sp)
	lw $t8, -204($sp)
	sw $t8, -8($sp)
	lw $t8, -8($sp)
	sw $t8, -208($sp)
	lw $t8, -208($sp)
	sgt $v1, $t8, 45
	sw $v1, -212($sp)
	lw $t8, -212($sp)
	beq $t8, $zero, func_funcB_block_93
	j func_funcB_block_91
func_funcB_block_91:
	j func_funcB_block_94
func_funcB_block_92:
	j func_funcB_block_93
func_funcB_block_93:
	j func_funcB_block_84
func_funcB_block_94:
	lw $t8, -8($sp)
	sw $t8, -216($sp)
	lw $a0, -216($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr2($zero)
	sw $t8, -220($sp)
	la $a0, g_dqr2($zero)
	li $v0, 4
	syscall
	j func_funcB_block_97
func_funcB_block_97:
	j func_funcB_block_98
func_funcB_block_98:
	lw $t8, -8($sp)
	sw $t8, -224($sp)
	lw $t8, -224($sp)
	addiu $v1, $t8, 2
	sw $v1, -228($sp)
	lw $t8, -228($sp)
	sw $t8, -8($sp)
	lw $t8, -8($sp)
	sw $t8, -232($sp)
	lw $t8, -232($sp)
	sgt $v1, $t8, 50
	sw $v1, -236($sp)
	lw $t8, -236($sp)
	beq $t8, $zero, func_funcB_block_105
	j func_funcB_block_103
func_funcB_block_103:
	j func_funcB_block_106
func_funcB_block_104:
	j func_funcB_block_105
func_funcB_block_105:
	j func_funcB_block_97
func_funcB_block_106:
	lw $t8, -8($sp)
	sw $t8, -240($sp)
	lw $a0, -240($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr3($zero)
	sw $t8, -244($sp)
	la $a0, g_dqr3($zero)
	li $v0, 4
	syscall
	lw $t8, -8($sp)
	sw $t8, -248($sp)
	lw $v0, -248($sp)
	lw $ra, -4($sp)
	jr $ra
func_funcC:
	sw $ra, -4($sp)
func_funcC_block_0:
	li $t8, 0
	sb $t8, -8($sp)
	j func_funcC_block_2
func_funcC_block_2:
	j func_funcC_block_3
func_funcC_block_3:
	lbu $t8, g_a1($zero)
	sw $t8, -12($sp)
	lw $t8, -12($sp)
	sb $t8, -8($sp)
	j func_funcC_block_5
func_funcC_block_5:
	j func_funcC_block_8
func_funcC_block_6:
	lbu $t8, g_a2($zero)
	sw $t8, -16($sp)
	lw $t8, -16($sp)
	sb $t8, -8($sp)
	j func_funcC_block_8
func_funcC_block_8:
	j func_funcC_block_13
func_funcC_block_9:
	j func_funcC_block_10
func_funcC_block_10:
	lbu $t8, g_a3($zero)
	sw $t8, -20($sp)
	lw $t8, -20($sp)
	sb $t8, -8($sp)
	j func_funcC_block_12
func_funcC_block_12:
	j func_funcC_block_13
func_funcC_block_13:
	lbu $t8, -8($sp)
	sw $t8, -24($sp)
	lw $v0, -24($sp)
	lw $ra, -4($sp)
	jr $ra
func_funcD:
	sw $ra, -4($sp)
func_funcD_block_1:
	sw $a0, -8($sp)
	lw $t8, -8($sp)
	sw $t8, -16($sp)
	lw $t8, -16($sp)
	sw $t8, -20($sp)
	lw $t8, -20($sp)
	lbu $t8, 0($t8)
	sw $t8, -24($sp)
	lw $a0, -24($sp)
	li $v0, 11
	syscall
	la $t8, g_dqr4($zero)
	sw $t8, -28($sp)
	la $a0, g_dqr4($zero)
	li $v0, 4
	syscall
	lw $ra, -4($sp)
	jr $ra
func_funcE:
	sw $ra, -4($sp)
func_funcE_block_2:
	sw $a0, -8($sp)
	sw $a1, -12($sp)
	lw $t8, -8($sp)
	sw $t8, -24($sp)
	lw $t8, -12($sp)
	sw $t8, -28($sp)
	lw $t8, -24($sp)
	lw $t9, -28($sp)
	seq $v1, $t8, $t9
	sw $v1, -32($sp)
	lw $t8, -32($sp)
	beq $t8, $zero, func_funcE_block_13
	j func_funcE_block_8
func_funcE_block_8:
	lw $t8, -8($sp)
	sw $t8, -36($sp)
	lw $t8, -12($sp)
	sw $t8, -40($sp)
	lw $t8, -36($sp)
	lw $t9, -40($sp)
	addu $v1, $t8, $t9
	sw $v1, -44($sp)
	lw $a0, -44($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr5($zero)
	sw $t8, -48($sp)
	la $a0, g_dqr5($zero)
	li $v0, 4
	syscall
	j func_funcE_block_13
func_funcE_block_13:
	lw $t8, -8($sp)
	sw $t8, -52($sp)
	lw $t8, -12($sp)
	sw $t8, -56($sp)
	lw $t8, -52($sp)
	lw $t9, -56($sp)
	sne $v1, $t8, $t9
	sw $v1, -60($sp)
	lw $t8, -60($sp)
	beq $t8, $zero, func_funcE_block_22
	j func_funcE_block_17
func_funcE_block_17:
	lw $t8, -8($sp)
	sw $t8, -64($sp)
	lw $t8, -12($sp)
	sw $t8, -68($sp)
	lw $t8, -64($sp)
	lw $t9, -68($sp)
	mul $v1, $t8, $t9
	sw $v1, -72($sp)
	lw $a0, -72($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr6($zero)
	sw $t8, -76($sp)
	la $a0, g_dqr6($zero)
	li $v0, 4
	syscall
	j func_funcE_block_22
func_funcE_block_22:
	lw $ra, -4($sp)
	jr $ra
func_main:
	sw $ra, -4($sp)
func_main_block_0:
	la $t8, g_dqr7($zero)
	sw $t8, -8($sp)
	la $a0, g_dqr7($zero)
	li $v0, 4
	syscall
	li $t8, 0
	sw $t8, -12($sp)
	li $t8, 0
	sb $t8, -16($sp)
	li $v0, 5
	syscall
	sw $v0, -20($sp)
	lw $t8, -20($sp)
	sw $t8, -12($sp)
	li $v0, 12
	syscall
	sw $v0, -24($sp)
	lw $t8, -24($sp)
	sb $t8, -16($sp)
	lw $t8, -12($sp)
	sw $t8, -28($sp)
	lbu $t8, -16($sp)
	sw $t8, -32($sp)
	lw $a0, -28($sp)
	li $v0, 1
	syscall
	li $a0, 32
	li $v0, 11
	syscall
	lw $a0, -32($sp)
	li $v0, 11
	syscall
	la $t8, g_dqr8($zero)
	sw $t8, -36($sp)
	la $a0, g_dqr8($zero)
	li $v0, 4
	syscall
	addu $fp, $sp, $zero
	addi $sp, $sp, -36
	jal func_funcA
	addi $sp, $sp, 36
	sw $v0, -40($sp)
	lw $t8, -12($sp)
	sw $t8, -48($sp)
	lw $t8, -48($sp)
	mul $v1, $t8, 10
	sw $v1, -52($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -52
	jal func_funcB
	addi $sp, $sp, 52
	sw $v0, -56($sp)
	lw $t8, -56($sp)
	div $v1, $t8, 2
	sw $v1, -60($sp)
	lw $t8, -52($sp)
	lw $t9, -60($sp)
	addu $v1, $t8, $t9
	sw $v1, -64($sp)
	lw $t8, -64($sp)
	subu $v1, $t8, 1
	sw $v1, -68($sp)
	lw $t8, -68($sp)
	rem $v1, $t8, 7
	sw $v1, -72($sp)
	lw $t8, -72($sp)
	sw $t8, -44($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -76
	jal func_funcC
	addi $sp, $sp, 76
	sw $v0, -80($sp)
	lw $t8, -80($sp)
	sb $t8, -76($sp)
	lw $t8, -44($sp)
	sw $t8, -84($sp)
	lbu $t8, -76($sp)
	sw $t8, -88($sp)
	lw $a0, -84($sp)
	li $v0, 1
	syscall
	li $a0, 32
	li $v0, 11
	syscall
	lw $a0, -88($sp)
	li $v0, 11
	syscall
	la $t8, g_dqr9($zero)
	sw $t8, -92($sp)
	la $a0, g_dqr9($zero)
	li $v0, 4
	syscall
	la $t8, g_a4($zero)
	sw $t8, -96($sp)
	li $t8, 122
	lw $t9, -96($sp)
	sb $t8, 0($t9)
	la $t8, g_a4($zero)
	sw $t8, -100($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -104
	lw $a0, -100($fp)
	jal func_funcD
	addi $sp, $sp, 104
	sw $v0, -104($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -112
	li $a0, 1
	li $a1, 2
	jal func_funcE
	addi $sp, $sp, 112
	sw $v0, -108($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -116
	li $a0, 1
	li $a1, 2
	jal func_funcE
	addi $sp, $sp, 116
	sw $v0, -112($sp)
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
