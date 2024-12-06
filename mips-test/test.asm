.data
	g_x: .word 0
	g_dqr0: .asciiz "21373457\n"
	g_dqr1: .asciiz "Empty for pass!\n"
	g_dqr2: .asciiz "One stmt for pass!\n"
	g_dqr3: .asciiz "Basic for and no params function pass!\n"
	g_dqr4: .asciiz "Please input 5 number (no zero)\n"
	g_dqr5: .asciiz "Basic for and one params function pass!\n"
	g_dqr6: .asciiz "Basic for and multiple params function pass!\n"
	g_dqr7: .asciiz "Recursive Success, count = "
	g_dqr8: .asciiz "\n"
	g_dqr9: .asciiz "This C level file include decl, if, for ,continue, break, basic cond. No block\n"
	g_dqr10: .asciiz "Pass Success!"


.text
	jal func_main
	li $v0, 10
	syscall

func_f1:
	sw $ra, -4($sp)
func_f1_block_0:
	li $t8, 0
	sw $t8, -8($sp)
	j func_f1_block_2
func_f1_block_2:
	lw $t8, -8($sp)
	sw $t8, -12($sp)
	lw $t8, -12($sp)
	slti $v1, $t8, 5
	sw $v1, -16($sp)
	lw $t8, -16($sp)
	beq $t8, $zero, func_f1_block_11
	j func_f1_block_5
func_f1_block_5:
	lw $t8, g_x($zero)
	sw $t8, -20($sp)
	lw $t8, -20($sp)
	addiu $v1, $t8, 1
	sw $v1, -24($sp)
	lw $t8, -24($sp)
	sw $t8, g_x($zero)
	j func_f1_block_8
func_f1_block_8:
	lw $t8, -8($sp)
	sw $t8, -28($sp)
	lw $t8, -28($sp)
	addiu $v1, $t8, 1
	sw $v1, -32($sp)
	lw $t8, -32($sp)
	sw $t8, -8($sp)
	j func_f1_block_2
func_f1_block_11:
	lw $ra, -4($sp)
	jr $ra
func_f2:
	sw $ra, -4($sp)
func_f2_block_0:
	lw $t8, g_x($zero)
	sw $t8, -8($sp)
	lw $t8, -8($sp)
	sgt $v1, $t8, 0
	sw $v1, -12($sp)
	lw $t8, -12($sp)
	beq $t8, $zero, func_f2_block_5
	j func_f2_block_3
func_f2_block_3:
	li $v0, -1
	lw $ra, -4($sp)
	jr $ra
func_f2_block_4:
	j func_f2_block_7
func_f2_block_5:
	li $v0, 1
	lw $ra, -4($sp)
	jr $ra
func_f2_block_6:
	j func_f2_block_7
func_f2_block_7:
	lw $t8, g_x($zero)
	sw $t8, -16($sp)
	lw $v0, -16($sp)
	lw $ra, -4($sp)
	jr $ra
func_f3:
	sw $ra, -4($sp)
func_f3_block_1:
	sw $a0, -12($sp)
	sw $t8, -8($sp)
	lw $t8, -8($sp)
	sw $t8, -16($sp)
	lw $t8, -16($sp)
	sw $t8, g_x($zero)
	lw $ra, -4($sp)
	jr $ra
func_f4:
	sw $ra, -4($sp)
func_f4_block_1:
	sw $a0, -12($sp)
	sw $t8, -8($sp)
	lw $t8, -8($sp)
	sw $t8, -16($sp)
	lw $t8, -16($sp)
	sgt $v1, $t8, 0
	sw $v1, -20($sp)
	lw $t8, -20($sp)
	beq $t8, $zero, func_f4_block_8
	j func_f4_block_5
func_f4_block_5:
	lw $t8, -8($sp)
	sw $t8, -24($sp)
	lw $v0, -24($sp)
	lw $ra, -4($sp)
	jr $ra
func_f4_block_7:
	j func_f4_block_8
func_f4_block_8:
	lw $t8, -8($sp)
	sw $t8, -28($sp)
	lw $t9, -28($sp)
	subu $v1, $t9, 0
	sw $v1, -32($sp)
	lw $v0, -32($sp)
	lw $ra, -4($sp)
	jr $ra
func_f5:
	sw $ra, -4($sp)
func_f5_block_3:
	sw $a0, -20($sp)
	sw $t8, -8($sp)
	sw $a1, -24($sp)
	sw $t8, -12($sp)
	sw $a2, -28($sp)
	sw $t8, -16($sp)
	lw $t8, -8($sp)
	sw $t8, -32($sp)
	lw $t8, -12($sp)
	sw $t8, -36($sp)
	lw $t8, -32($sp)
	lw $t9, -36($sp)
	sgt $v1, $t8, $t9
	sw $v1, -40($sp)
	lw $t8, -40($sp)
	beq $t8, $zero, func_f5_block_21
	j func_f5_block_10
func_f5_block_10:
	lw $t8, -8($sp)
	sw $t8, -44($sp)
	lw $t8, -16($sp)
	sw $t8, -48($sp)
	lw $t8, -44($sp)
	lw $t9, -48($sp)
	sgt $v1, $t8, $t9
	sw $v1, -52($sp)
	lw $t8, -52($sp)
	beq $t8, $zero, func_f5_block_17
	j func_f5_block_14
func_f5_block_14:
	lw $t8, -8($sp)
	sw $t8, -56($sp)
	lw $v0, -56($sp)
	lw $ra, -4($sp)
	jr $ra
func_f5_block_16:
	j func_f5_block_20
func_f5_block_17:
	lw $t8, -16($sp)
	sw $t8, -60($sp)
	lw $v0, -60($sp)
	lw $ra, -4($sp)
	jr $ra
func_f5_block_19:
	j func_f5_block_20
func_f5_block_20:
	j func_f5_block_21
func_f5_block_21:
	lw $t8, -12($sp)
	sw $t8, -64($sp)
	lw $t8, -16($sp)
	sw $t8, -68($sp)
	lw $t8, -64($sp)
	lw $t9, -68($sp)
	sgt $v1, $t8, $t9
	sw $v1, -72($sp)
	lw $t8, -72($sp)
	beq $t8, $zero, func_f5_block_36
	j func_f5_block_25
func_f5_block_25:
	lw $t8, -12($sp)
	sw $t8, -76($sp)
	lw $t8, -8($sp)
	sw $t8, -80($sp)
	lw $t8, -76($sp)
	lw $t9, -80($sp)
	sgt $v1, $t8, $t9
	sw $v1, -84($sp)
	lw $t8, -84($sp)
	beq $t8, $zero, func_f5_block_32
	j func_f5_block_29
func_f5_block_29:
	lw $t8, -12($sp)
	sw $t8, -88($sp)
	lw $v0, -88($sp)
	lw $ra, -4($sp)
	jr $ra
func_f5_block_31:
	j func_f5_block_35
func_f5_block_32:
	lw $t8, -8($sp)
	sw $t8, -92($sp)
	lw $v0, -92($sp)
	lw $ra, -4($sp)
	jr $ra
func_f5_block_34:
	j func_f5_block_35
func_f5_block_35:
	j func_f5_block_36
func_f5_block_36:
	lw $t8, -16($sp)
	sw $t8, -96($sp)
	lw $t8, -8($sp)
	sw $t8, -100($sp)
	lw $t8, -96($sp)
	lw $t9, -100($sp)
	sgt $v1, $t8, $t9
	sw $v1, -104($sp)
	lw $t8, -104($sp)
	beq $t8, $zero, func_f5_block_51
	j func_f5_block_40
func_f5_block_40:
	lw $t8, -16($sp)
	sw $t8, -108($sp)
	lw $t8, -12($sp)
	sw $t8, -112($sp)
	lw $t8, -108($sp)
	lw $t9, -112($sp)
	sgt $v1, $t8, $t9
	sw $v1, -116($sp)
	lw $t8, -116($sp)
	beq $t8, $zero, func_f5_block_47
	j func_f5_block_44
func_f5_block_44:
	lw $t8, -16($sp)
	sw $t8, -120($sp)
	lw $v0, -120($sp)
	lw $ra, -4($sp)
	jr $ra
func_f5_block_46:
	j func_f5_block_50
func_f5_block_47:
	lw $t8, -12($sp)
	sw $t8, -124($sp)
	lw $v0, -124($sp)
	lw $ra, -4($sp)
	jr $ra
func_f5_block_49:
	j func_f5_block_50
func_f5_block_50:
	j func_f5_block_51
func_f5_block_51:
	lw $t8, -8($sp)
	sw $t8, -128($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -132
	lw $a0, -128($sp)
	jal func_f4
	addi $sp, $sp, 132
	lw $v0, -132($sp)
	lw $v0, -132($sp)
	lw $ra, -4($sp)
	jr $ra
func_f6:
	sw $ra, -4($sp)
func_f6_block_1:
	sw $a0, -12($sp)
	sw $t8, -8($sp)
	lw $t8, g_x($zero)
	sw $t8, -16($sp)
	lw $t8, -8($sp)
	sw $t8, -20($sp)
	lw $t8, -16($sp)
	lw $t9, -20($sp)
	addu $v1, $t8, $t9
	sw $v1, -24($sp)
	lw $t8, -24($sp)
	sw $t8, g_x($zero)
	lw $t8, -8($sp)
	sw $t8, -28($sp)
	lw $t8, -28($sp)
	seq $v1, $t8, 0
	sw $v1, -32($sp)
	lw $t8, -32($sp)
	beq $t8, $zero, func_f6_block_10
	j func_f6_block_8
func_f6_block_8:
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
func_f6_block_9:
	j func_f6_block_10
func_f6_block_10:
	lw $t8, -8($sp)
	sw $t8, -36($sp)
	lw $t8, -36($sp)
	subu $v1, $t8, 1
	sw $v1, -40($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -44
	lw $a0, -40($sp)
	jal func_f6
	addi $sp, $sp, 44
	lw $v0, -44($sp)
	lw $v0, -44($sp)
	lw $ra, -4($sp)
	jr $ra
func_main:
	sw $ra, -4($sp)
func_main_block_0:
	la $t8, g_dqr0($zero)
	sw $t8, -8($sp)
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	li $t8, 5
	sw $t8, -16($sp)
	li $t8, 0
	sw $t8, -12($sp)
	j func_main_block_5
func_main_block_5:
	lw $t8, -12($sp)
	sw $t8, -24($sp)
	lw $t8, -24($sp)
	slti $v1, $t8, 5
	sw $v1, -28($sp)
	lw $t8, -28($sp)
	beq $t8, $zero, func_main_block_12
	j func_main_block_8
func_main_block_8:
	j func_main_block_9
func_main_block_9:
	lw $t8, -12($sp)
	sw $t8, -32($sp)
	lw $t8, -32($sp)
	addiu $v1, $t8, 1
	sw $v1, -36($sp)
	lw $t8, -36($sp)
	sw $t8, -12($sp)
	j func_main_block_5
func_main_block_12:
	lw $t8, -12($sp)
	sw $t8, -40($sp)
	lw $t8, -40($sp)
	seq $v1, $t8, 5
	sw $v1, -44($sp)
	lw $t8, -44($sp)
	beq $t8, $zero, func_main_block_17
	j func_main_block_15
func_main_block_15:
	la $t8, g_dqr1($zero)
	sw $t8, -48($sp)
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	j func_main_block_17
func_main_block_17:
	li $t8, 0
	sw $t8, -12($sp)
	j func_main_block_18
func_main_block_18:
	lw $t8, -12($sp)
	sw $t8, -52($sp)
	lw $t8, -52($sp)
	slti $v1, $t8, 2
	sw $v1, -56($sp)
	lw $t8, -56($sp)
	beq $t8, $zero, func_main_block_24
	j func_main_block_21
func_main_block_21:
	lw $t8, -12($sp)
	sw $t8, -60($sp)
	lw $t8, -60($sp)
	addiu $v1, $t8, 1
	sw $v1, -64($sp)
	lw $t8, -64($sp)
	sw $t8, -12($sp)
	j func_main_block_18
func_main_block_24:
	li $t8, 2
	sw $t8, -12($sp)
	j func_main_block_25
func_main_block_25:
	j func_main_block_26
func_main_block_26:
	lw $t8, -12($sp)
	sw $t8, -68($sp)
	lw $t8, -68($sp)
	seq $v1, $t8, 4
	sw $v1, -72($sp)
	lw $t8, -72($sp)
	beq $t8, $zero, func_main_block_31
	j func_main_block_29
func_main_block_29:
	j func_main_block_35
func_main_block_30:
	j func_main_block_31
func_main_block_31:
	j func_main_block_32
func_main_block_32:
	lw $t8, -12($sp)
	sw $t8, -76($sp)
	lw $t8, -76($sp)
	addiu $v1, $t8, 1
	sw $v1, -80($sp)
	lw $t8, -80($sp)
	sw $t8, -12($sp)
	j func_main_block_25
func_main_block_35:
	j func_main_block_36
func_main_block_36:
	lw $t8, -12($sp)
	sw $t8, -84($sp)
	lw $t8, -84($sp)
	slti $v1, $t8, 5
	sw $v1, -88($sp)
	lw $t8, -88($sp)
	beq $t8, $zero, func_main_block_50
	j func_main_block_39
func_main_block_39:
	lw $t8, -12($sp)
	sw $t8, -92($sp)
	lw $t8, -92($sp)
	slti $v1, $t8, 5
	sw $v1, -96($sp)
	lw $t8, -96($sp)
	beq $t8, $zero, func_main_block_44
	j func_main_block_42
func_main_block_42:
	j func_main_block_47
func_main_block_43:
	j func_main_block_44
func_main_block_44:
	lw $t8, -12($sp)
	sw $t8, -100($sp)
	lw $t8, -100($sp)
	addiu $v1, $t8, 2
	sw $v1, -104($sp)
	lw $t8, -104($sp)
	sw $t8, -12($sp)
	j func_main_block_47
func_main_block_47:
	lw $t8, -12($sp)
	sw $t8, -108($sp)
	lw $t8, -108($sp)
	addiu $v1, $t8, 1
	sw $v1, -112($sp)
	lw $t8, -112($sp)
	sw $t8, -12($sp)
	j func_main_block_36
func_main_block_50:
	li $t8, 5
	sw $t8, -12($sp)
	j func_main_block_51
func_main_block_51:
	j func_main_block_52
func_main_block_52:
	lw $t8, -12($sp)
	sw $t8, -116($sp)
	lw $t8, -116($sp)
	addiu $v1, $t8, 1
	sw $v1, -120($sp)
	lw $t8, -120($sp)
	sw $t8, -12($sp)
	lw $t8, -12($sp)
	sw $t8, -124($sp)
	lw $t8, -124($sp)
	seq $v1, $t8, 6
	sw $v1, -128($sp)
	lw $t8, -128($sp)
	beq $t8, $zero, func_main_block_59
	j func_main_block_57
func_main_block_57:
	j func_main_block_60
func_main_block_58:
	j func_main_block_59
func_main_block_59:
	j func_main_block_51
func_main_block_60:
	j func_main_block_61
func_main_block_61:
	lw $t8, -12($sp)
	sw $t8, -132($sp)
	lw $t8, -132($sp)
	slti $v1, $t8, 7
	sw $v1, -136($sp)
	lw $t8, -136($sp)
	beq $t8, $zero, func_main_block_67
	j func_main_block_64
func_main_block_64:
	lw $t8, -12($sp)
	sw $t8, -140($sp)
	lw $t8, -140($sp)
	addiu $v1, $t8, 1
	sw $v1, -144($sp)
	lw $t8, -144($sp)
	sw $t8, -12($sp)
	j func_main_block_61
func_main_block_67:
	j func_main_block_68
func_main_block_68:
	j func_main_block_69
func_main_block_69:
	lw $t8, -12($sp)
	sw $t8, -148($sp)
	lw $t8, -148($sp)
	seq $v1, $t8, 8
	sw $v1, -152($sp)
	lw $t8, -152($sp)
	beq $t8, $zero, func_main_block_74
	j func_main_block_72
func_main_block_72:
	j func_main_block_78
func_main_block_73:
	j func_main_block_74
func_main_block_74:
	j func_main_block_75
func_main_block_75:
	lw $t8, -12($sp)
	sw $t8, -156($sp)
	lw $t8, -156($sp)
	addiu $v1, $t8, 1
	sw $v1, -160($sp)
	lw $t8, -160($sp)
	sw $t8, -12($sp)
	j func_main_block_68
func_main_block_78:
	j func_main_block_79
func_main_block_79:
	j func_main_block_80
func_main_block_80:
	lw $t8, -12($sp)
	sw $t8, -164($sp)
	lw $t8, -164($sp)
	addiu $v1, $t8, 1
	sw $v1, -168($sp)
	lw $t8, -168($sp)
	sw $t8, -12($sp)
	lw $t8, -12($sp)
	sw $t8, -172($sp)
	lw $t8, -172($sp)
	seq $v1, $t8, 10
	sw $v1, -176($sp)
	lw $t8, -176($sp)
	beq $t8, $zero, func_main_block_88
	j func_main_block_85
func_main_block_85:
	la $t8, g_dqr2($zero)
	sw $t8, -180($sp)
	la $a0, g_dqr2($zero)
	li $v0, 4
	syscall
	j func_main_block_89
func_main_block_87:
	j func_main_block_88
func_main_block_88:
	j func_main_block_79
func_main_block_89:
	addu $fp, $sp, $zero
	addi $sp, $sp, -180
	jal func_f1
	addi $sp, $sp, 180
	lw $v0, -184($sp)
	lw $t8, g_x($zero)
	sw $t8, -188($sp)
	lw $t8, -188($sp)
	seq $v1, $t8, 5
	sw $v1, -192($sp)
	lw $t8, -192($sp)
	beq $t8, $zero, func_main_block_98
	j func_main_block_92
func_main_block_92:
	addu $fp, $sp, $zero
	addi $sp, $sp, -192
	jal func_f2
	addi $sp, $sp, 192
	lw $v0, -196($sp)
	lw $t8, -196($sp)
	seq $v1, $t8, -1
	sw $v1, -200($sp)
	lw $t8, -200($sp)
	beq $t8, $zero, func_main_block_97
	j func_main_block_95
func_main_block_95:
	la $t8, g_dqr3($zero)
	sw $t8, -204($sp)
	la $a0, g_dqr3($zero)
	li $v0, 4
	syscall
	j func_main_block_97
func_main_block_97:
	j func_main_block_98
func_main_block_98:
	la $t8, g_dqr4($zero)
	sw $t8, -208($sp)
	la $a0, g_dqr4($zero)
	li $v0, 4
	syscall
	li $t8, -1
	sw $t8, g_x($zero)
	li $t8, 0
	sw $t8, -12($sp)
	j func_main_block_100
func_main_block_100:
	lw $t8, -12($sp)
	sw $t8, -212($sp)
	lw $t8, -12($sp)
	sw $t8, -216($sp)
	lw $t8, -212($sp)
	lw $t9, -216($sp)
	mul $v1, $t8, $t9
	sw $v1, -220($sp)
	lw $t8, -16($sp)
	sw $t8, -224($sp)
	lw $t8, -16($sp)
	sw $t8, -228($sp)
	lw $t8, -224($sp)
	lw $t9, -228($sp)
	mul $v1, $t8, $t9
	sw $v1, -232($sp)
	lw $t8, -220($sp)
	lw $t9, -232($sp)
	slt $v1, $t8, $t9
	sw $v1, -236($sp)
	lw $t8, -236($sp)
	beq $t8, $zero, func_main_block_127
	j func_main_block_108
func_main_block_108:
	li $v0, 5
	syscall
	sw $v0, -240($sp)
	lw $t8, -240($sp)
	sw $t8, -20($sp)
	lw $t8, -20($sp)
	sw $t8, -244($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -248
	lw $a0, -244($sp)
	jal func_f4
	addi $sp, $sp, 248
	lw $v0, -248($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -252
	lw $a0, -248($sp)
	jal func_f3
	addi $sp, $sp, 252
	lw $v0, -252($sp)
	lw $t8, g_x($zero)
	sw $t8, -256($sp)
	lw $t8, -256($sp)
	slti $v1, $t8, 0
	sw $v1, -260($sp)
	lw $t8, -260($sp)
	beq $t8, $zero, func_main_block_116
	j func_main_block_114
func_main_block_114:
	j func_main_block_127
func_main_block_115:
	j func_main_block_116
func_main_block_116:
	lw $t8, g_x($zero)
	sw $t8, -264($sp)
	lw $t8, -264($sp)
	sgt $v1, $t8, 0
	sw $v1, -268($sp)
	lw $t8, -268($sp)
	beq $t8, $zero, func_main_block_121
	j func_main_block_119
func_main_block_119:
	j func_main_block_124
func_main_block_120:
	j func_main_block_121
func_main_block_121:
	lw $t8, -12($sp)
	sw $t8, -272($sp)
	lw $t8, -272($sp)
	addiu $v1, $t8, 1
	sw $v1, -276($sp)
	lw $t8, -276($sp)
	sw $t8, -12($sp)
	j func_main_block_124
func_main_block_124:
	lw $t8, -12($sp)
	sw $t8, -280($sp)
	lw $t8, -280($sp)
	addiu $v1, $t8, 1
	sw $v1, -284($sp)
	lw $t8, -284($sp)
	sw $t8, -12($sp)
	j func_main_block_100
func_main_block_127:
	lw $t8, g_x($zero)
	sw $t8, -288($sp)
	lw $t8, -288($sp)
	sge $v1, $t8, 0
	sw $v1, -292($sp)
	lw $t8, -292($sp)
	beq $t8, $zero, func_main_block_132
	j func_main_block_130
func_main_block_130:
	la $t8, g_dqr5($zero)
	sw $t8, -296($sp)
	la $a0, g_dqr5($zero)
	li $v0, 4
	syscall
	j func_main_block_132
func_main_block_132:
	li $t8, 10
	sw $t8, -12($sp)
	li $t8, 5
	sw $t8, -16($sp)
	li $t8, 7
	sw $t8, -20($sp)
	lw $t8, -12($sp)
	sw $t8, -300($sp)
	lw $t8, -16($sp)
	sw $t8, -304($sp)
	lw $t8, -20($sp)
	sw $t8, -308($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -320
	lw $a0, -300($sp)
	lw $a1, -304($sp)
	lw $a2, -308($sp)
	jal func_f5
	addi $sp, $sp, 320
	lw $v0, -312($sp)
	lw $t8, -12($sp)
	sw $t8, -316($sp)
	lw $t8, -312($sp)
	lw $t9, -316($sp)
	seq $v1, $t8, $t9
	sw $v1, -320($sp)
	lw $t8, -320($sp)
	beq $t8, $zero, func_main_block_141
	j func_main_block_139
func_main_block_139:
	la $t8, g_dqr6($zero)
	sw $t8, -324($sp)
	la $a0, g_dqr6($zero)
	li $v0, 4
	syscall
	j func_main_block_141
func_main_block_141:
	li $t8, 0
	sw $t8, g_x($zero)
	addu $fp, $sp, $zero
	addi $sp, $sp, -328
	li $a0, 10
	jal func_f6
	addi $sp, $sp, 328
	lw $v0, -328($sp)
	lw $t8, g_x($zero)
	sw $t8, -332($sp)
	la $t8, g_dqr7($zero)
	sw $t8, -336($sp)
	la $a0, g_dqr7($zero)
	li $v0, 4
	syscall
	lw $a0, -332($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr8($zero)
	sw $t8, -340($sp)
	la $a0, g_dqr8($zero)
	li $v0, 4
	syscall
	la $t8, g_dqr9($zero)
	sw $t8, -344($sp)
	la $a0, g_dqr9($zero)
	li $v0, 4
	syscall
	la $t8, g_dqr10($zero)
	sw $t8, -348($sp)
	la $a0, g_dqr10($zero)
	li $v0, 4
	syscall
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
