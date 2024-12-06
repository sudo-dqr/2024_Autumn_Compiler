.data
	g_x: .word 0
	g_dqr0: .asciiz "21373457"
	g_dqr1: .asciiz "Empty for pass!"
	g_dqr2: .asciiz "One stmt for pass!"
	g_dqr3: .asciiz "Basic for and no params function pass!"
	g_dqr4: .asciiz "Please input 5 number (no zero)"
	g_dqr5: .asciiz "Basic for and one params function pass!"
	g_dqr6: .asciiz "Basic for and multiple params function pass!"
	g_dqr7: .asciiz "Recursive Success, count = "
	g_dqr8: .asciiz "This C level file include decl, if, for ,continue, break, basic cond. No block"
	g_dqr9: .asciiz "Pass Success!"


.text
	jal func_main
	li $v0, 10
	syscall

func_f1:
	sw $sp, -4($ra)
func_f1_block_0:
	li $t8, 0
	sw $sp, -8($t8)
	j func_f1_block_2
func_f1_block_2:
	lw $sp, -8($t8)
	sw $sp, -12($t8)
	lw $sp, -12($t8)
	slti $v1, $t8, 5
	sw $sp, -16($v1)
	lw $sp, -16($t8)
	beq $t8, $zero, func_f1_block_11
	j func_f1_block_5
func_f1_block_5:
	lw $zero, g_x($t8)
	sw $sp, -20($t8)
	lw $sp, -20($t8)
	addiu $v1, $t8, 1
	sw $sp, -24($v1)
	lw $sp, -24($t8)
	sw $zero, g_x($t8)
	j func_f1_block_8
func_f1_block_8:
	lw $sp, -8($t8)
	sw $sp, -28($t8)
	lw $sp, -28($t8)
	addiu $v1, $t8, 1
	sw $sp, -32($v1)
	lw $sp, -32($t8)
	sw $sp, -8($t8)
	j func_f1_block_2
func_f1_block_11:
	lw $sp, -4($ra)
	jr $ra
func_f2:
	sw $sp, -4($ra)
func_f2_block_0:
	lw $zero, g_x($t8)
	sw $sp, -8($t8)
	lw $sp, -8($t8)
	sgt $v1, $t8, 0
	sw $sp, -12($v1)
	lw $sp, -12($t8)
	beq $t8, $zero, func_f2_block_5
	j func_f2_block_3
func_f2_block_3:
	li $v0, -1
	lw $sp, -4($ra)
	jr $ra
func_f2_block_4:
	j func_f2_block_7
func_f2_block_5:
	li $v0, 1
	lw $sp, -4($ra)
	jr $ra
func_f2_block_6:
	j func_f2_block_7
func_f2_block_7:
	lw $zero, g_x($t8)
	sw $sp, -16($t8)
	lw $sp, -16($v0)
	lw $sp, -4($ra)
	jr $ra
func_f3:
	sw $sp, -4($ra)
func_f3_block_1:
	sw $sp, -12($a0)
	sw $sp, -8($t8)
	lw $sp, -8($t8)
	sw $sp, -16($t8)
	lw $sp, -16($t8)
	sw $zero, g_x($t8)
	lw $sp, -4($ra)
	jr $ra
func_f4:
	sw $sp, -4($ra)
func_f4_block_1:
	sw $sp, -12($a0)
	sw $sp, -8($t8)
	lw $sp, -8($t8)
	sw $sp, -16($t8)
	lw $sp, -16($t8)
	sgt $v1, $t8, 0
	sw $sp, -20($v1)
	lw $sp, -20($t8)
	beq $t8, $zero, func_f4_block_8
	j func_f4_block_5
func_f4_block_5:
	lw $sp, -8($t8)
	sw $sp, -24($t8)
	lw $sp, -24($v0)
	lw $sp, -4($ra)
	jr $ra
func_f4_block_7:
	j func_f4_block_8
func_f4_block_8:
	lw $sp, -8($t8)
	sw $sp, -28($t8)
	lw $sp, -28($t9)
	subu $t9, $v1, 0
	sw $sp, -32($v1)
	lw $sp, -32($v0)
	lw $sp, -4($ra)
	jr $ra
func_f5:
	sw $sp, -4($ra)
func_f5_block_3:
	sw $sp, -20($a0)
	sw $sp, -8($t8)
	sw $sp, -24($a1)
	sw $sp, -12($t8)
	sw $sp, -28($a2)
	sw $sp, -16($t8)
	lw $sp, -8($t8)
	sw $sp, -32($t8)
	lw $sp, -12($t8)
	sw $sp, -36($t8)
	lw $sp, -32($t8)
	lw $sp, -36($t9)
	sgt $v1, $t8, $t9
	sw $sp, -40($v1)
	lw $sp, -40($t8)
	beq $t8, $zero, func_f5_block_21
	j func_f5_block_10
func_f5_block_10:
	lw $sp, -8($t8)
	sw $sp, -44($t8)
	lw $sp, -16($t8)
	sw $sp, -48($t8)
	lw $sp, -44($t8)
	lw $sp, -48($t9)
	sgt $v1, $t8, $t9
	sw $sp, -52($v1)
	lw $sp, -52($t8)
	beq $t8, $zero, func_f5_block_17
	j func_f5_block_14
func_f5_block_14:
	lw $sp, -8($t8)
	sw $sp, -56($t8)
	lw $sp, -56($v0)
	lw $sp, -4($ra)
	jr $ra
func_f5_block_16:
	j func_f5_block_20
func_f5_block_17:
	lw $sp, -16($t8)
	sw $sp, -60($t8)
	lw $sp, -60($v0)
	lw $sp, -4($ra)
	jr $ra
func_f5_block_19:
	j func_f5_block_20
func_f5_block_20:
	j func_f5_block_21
func_f5_block_21:
	lw $sp, -12($t8)
	sw $sp, -64($t8)
	lw $sp, -16($t8)
	sw $sp, -68($t8)
	lw $sp, -64($t8)
	lw $sp, -68($t9)
	sgt $v1, $t8, $t9
	sw $sp, -72($v1)
	lw $sp, -72($t8)
	beq $t8, $zero, func_f5_block_36
	j func_f5_block_25
func_f5_block_25:
	lw $sp, -12($t8)
	sw $sp, -76($t8)
	lw $sp, -8($t8)
	sw $sp, -80($t8)
	lw $sp, -76($t8)
	lw $sp, -80($t9)
	sgt $v1, $t8, $t9
	sw $sp, -84($v1)
	lw $sp, -84($t8)
	beq $t8, $zero, func_f5_block_32
	j func_f5_block_29
func_f5_block_29:
	lw $sp, -12($t8)
	sw $sp, -88($t8)
	lw $sp, -88($v0)
	lw $sp, -4($ra)
	jr $ra
func_f5_block_31:
	j func_f5_block_35
func_f5_block_32:
	lw $sp, -8($t8)
	sw $sp, -92($t8)
	lw $sp, -92($v0)
	lw $sp, -4($ra)
	jr $ra
func_f5_block_34:
	j func_f5_block_35
func_f5_block_35:
	j func_f5_block_36
func_f5_block_36:
	lw $sp, -16($t8)
	sw $sp, -96($t8)
	lw $sp, -8($t8)
	sw $sp, -100($t8)
	lw $sp, -96($t8)
	lw $sp, -100($t9)
	sgt $v1, $t8, $t9
	sw $sp, -104($v1)
	lw $sp, -104($t8)
	beq $t8, $zero, func_f5_block_51
	j func_f5_block_40
func_f5_block_40:
	lw $sp, -16($t8)
	sw $sp, -108($t8)
	lw $sp, -12($t8)
	sw $sp, -112($t8)
	lw $sp, -108($t8)
	lw $sp, -112($t9)
	sgt $v1, $t8, $t9
	sw $sp, -116($v1)
	lw $sp, -116($t8)
	beq $t8, $zero, func_f5_block_47
	j func_f5_block_44
func_f5_block_44:
	lw $sp, -16($t8)
	sw $sp, -120($t8)
	lw $sp, -120($v0)
	lw $sp, -4($ra)
	jr $ra
func_f5_block_46:
	j func_f5_block_50
func_f5_block_47:
	lw $sp, -12($t8)
	sw $sp, -124($t8)
	lw $sp, -124($v0)
	lw $sp, -4($ra)
	jr $ra
func_f5_block_49:
	j func_f5_block_50
func_f5_block_50:
	j func_f5_block_51
func_f5_block_51:
	lw $sp, -8($t8)
	sw $sp, -128($t8)
	addu $fp, $sp, $zero
	addi $sp, $sp, -132
	lw $sp, -128($a0)
	jal func_f4
	addi $sp, $sp, 132
	lw $sp, -132($v0)
	lw $sp, -132($v0)
	lw $sp, -4($ra)
	jr $ra
func_f6:
	sw $sp, -4($ra)
func_f6_block_1:
	sw $sp, -12($a0)
	sw $sp, -8($t8)
	lw $zero, g_x($t8)
	sw $sp, -16($t8)
	lw $sp, -8($t8)
	sw $sp, -20($t8)
	lw $sp, -16($t8)
	lw $sp, -20($t9)
	addu $v1, $t8, $t9
	sw $sp, -24($v1)
	lw $sp, -24($t8)
	sw $zero, g_x($t8)
	lw $sp, -8($t8)
	sw $sp, -28($t8)
	lw $sp, -28($t8)
	seq $v1, $t8, 0
	sw $sp, -32($v1)
	lw $sp, -32($t8)
	beq $t8, $zero, func_f6_block_10
	j func_f6_block_8
func_f6_block_8:
	li $v0, 0
	lw $sp, -4($ra)
	jr $ra
func_f6_block_9:
	j func_f6_block_10
func_f6_block_10:
	lw $sp, -8($t8)
	sw $sp, -36($t8)
	lw $sp, -36($t8)
	subu $t8, $v1, 1
	sw $sp, -40($v1)
	addu $fp, $sp, $zero
	addi $sp, $sp, -44
	lw $sp, -40($a0)
	jal func_f6
	addi $sp, $sp, 44
	lw $sp, -44($v0)
	lw $sp, -44($v0)
	lw $sp, -4($ra)
	jr $ra
func_main:
	sw $sp, -4($ra)
func_main_block_0:
	la $t8, g_dqr0($zero)
	sw $sp, -8($t8)
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	li $a0, 10
	li $v0, 11
	syscall
	li $t8, 5
	sw $sp, -16($t8)
	li $t8, 0
	sw $sp, -12($t8)
	j func_main_block_5
func_main_block_5:
	lw $sp, -12($t8)
	sw $sp, -24($t8)
	lw $sp, -24($t8)
	slti $v1, $t8, 5
	sw $sp, -28($v1)
	lw $sp, -28($t8)
	beq $t8, $zero, func_main_block_12
	j func_main_block_8
func_main_block_8:
	j func_main_block_9
func_main_block_9:
	lw $sp, -12($t8)
	sw $sp, -32($t8)
	lw $sp, -32($t8)
	addiu $v1, $t8, 1
	sw $sp, -36($v1)
	lw $sp, -36($t8)
	sw $sp, -12($t8)
	j func_main_block_5
func_main_block_12:
	lw $sp, -12($t8)
	sw $sp, -40($t8)
	lw $sp, -40($t8)
	seq $v1, $t8, 5
	sw $sp, -44($v1)
	lw $sp, -44($t8)
	beq $t8, $zero, func_main_block_17
	j func_main_block_15
func_main_block_15:
	la $t8, g_dqr1($zero)
	sw $sp, -48($t8)
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	li $a0, 10
	li $v0, 11
	syscall
	j func_main_block_17
func_main_block_17:
	li $t8, 0
	sw $sp, -12($t8)
	j func_main_block_18
func_main_block_18:
	lw $sp, -12($t8)
	sw $sp, -52($t8)
	lw $sp, -52($t8)
	slti $v1, $t8, 2
	sw $sp, -56($v1)
	lw $sp, -56($t8)
	beq $t8, $zero, func_main_block_24
	j func_main_block_21
func_main_block_21:
	lw $sp, -12($t8)
	sw $sp, -60($t8)
	lw $sp, -60($t8)
	addiu $v1, $t8, 1
	sw $sp, -64($v1)
	lw $sp, -64($t8)
	sw $sp, -12($t8)
	j func_main_block_18
func_main_block_24:
	li $t8, 2
	sw $sp, -12($t8)
	j func_main_block_25
func_main_block_25:
	j func_main_block_26
func_main_block_26:
	lw $sp, -12($t8)
	sw $sp, -68($t8)
	lw $sp, -68($t8)
	seq $v1, $t8, 4
	sw $sp, -72($v1)
	lw $sp, -72($t8)
	beq $t8, $zero, func_main_block_31
	j func_main_block_29
func_main_block_29:
	j func_main_block_35
func_main_block_30:
	j func_main_block_31
func_main_block_31:
	j func_main_block_32
func_main_block_32:
	lw $sp, -12($t8)
	sw $sp, -76($t8)
	lw $sp, -76($t8)
	addiu $v1, $t8, 1
	sw $sp, -80($v1)
	lw $sp, -80($t8)
	sw $sp, -12($t8)
	j func_main_block_25
func_main_block_35:
	j func_main_block_36
func_main_block_36:
	lw $sp, -12($t8)
	sw $sp, -84($t8)
	lw $sp, -84($t8)
	slti $v1, $t8, 5
	sw $sp, -88($v1)
	lw $sp, -88($t8)
	beq $t8, $zero, func_main_block_50
	j func_main_block_39
func_main_block_39:
	lw $sp, -12($t8)
	sw $sp, -92($t8)
	lw $sp, -92($t8)
	slti $v1, $t8, 5
	sw $sp, -96($v1)
	lw $sp, -96($t8)
	beq $t8, $zero, func_main_block_44
	j func_main_block_42
func_main_block_42:
	j func_main_block_47
func_main_block_43:
	j func_main_block_44
func_main_block_44:
	lw $sp, -12($t8)
	sw $sp, -100($t8)
	lw $sp, -100($t8)
	addiu $v1, $t8, 2
	sw $sp, -104($v1)
	lw $sp, -104($t8)
	sw $sp, -12($t8)
	j func_main_block_47
func_main_block_47:
	lw $sp, -12($t8)
	sw $sp, -108($t8)
	lw $sp, -108($t8)
	addiu $v1, $t8, 1
	sw $sp, -112($v1)
	lw $sp, -112($t8)
	sw $sp, -12($t8)
	j func_main_block_36
func_main_block_50:
	li $t8, 5
	sw $sp, -12($t8)
	j func_main_block_51
func_main_block_51:
	j func_main_block_52
func_main_block_52:
	lw $sp, -12($t8)
	sw $sp, -116($t8)
	lw $sp, -116($t8)
	addiu $v1, $t8, 1
	sw $sp, -120($v1)
	lw $sp, -120($t8)
	sw $sp, -12($t8)
	lw $sp, -12($t8)
	sw $sp, -124($t8)
	lw $sp, -124($t8)
	seq $v1, $t8, 6
	sw $sp, -128($v1)
	lw $sp, -128($t8)
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
	lw $sp, -12($t8)
	sw $sp, -132($t8)
	lw $sp, -132($t8)
	slti $v1, $t8, 7
	sw $sp, -136($v1)
	lw $sp, -136($t8)
	beq $t8, $zero, func_main_block_67
	j func_main_block_64
func_main_block_64:
	lw $sp, -12($t8)
	sw $sp, -140($t8)
	lw $sp, -140($t8)
	addiu $v1, $t8, 1
	sw $sp, -144($v1)
	lw $sp, -144($t8)
	sw $sp, -12($t8)
	j func_main_block_61
func_main_block_67:
	j func_main_block_68
func_main_block_68:
	j func_main_block_69
func_main_block_69:
	lw $sp, -12($t8)
	sw $sp, -148($t8)
	lw $sp, -148($t8)
	seq $v1, $t8, 8
	sw $sp, -152($v1)
	lw $sp, -152($t8)
	beq $t8, $zero, func_main_block_74
	j func_main_block_72
func_main_block_72:
	j func_main_block_78
func_main_block_73:
	j func_main_block_74
func_main_block_74:
	j func_main_block_75
func_main_block_75:
	lw $sp, -12($t8)
	sw $sp, -156($t8)
	lw $sp, -156($t8)
	addiu $v1, $t8, 1
	sw $sp, -160($v1)
	lw $sp, -160($t8)
	sw $sp, -12($t8)
	j func_main_block_68
func_main_block_78:
	j func_main_block_79
func_main_block_79:
	j func_main_block_80
func_main_block_80:
	lw $sp, -12($t8)
	sw $sp, -164($t8)
	lw $sp, -164($t8)
	addiu $v1, $t8, 1
	sw $sp, -168($v1)
	lw $sp, -168($t8)
	sw $sp, -12($t8)
	lw $sp, -12($t8)
	sw $sp, -172($t8)
	lw $sp, -172($t8)
	seq $v1, $t8, 10
	sw $sp, -176($v1)
	lw $sp, -176($t8)
	beq $t8, $zero, func_main_block_88
	j func_main_block_85
func_main_block_85:
	la $t8, g_dqr2($zero)
	sw $sp, -180($t8)
	la $a0, g_dqr2($zero)
	li $v0, 4
	syscall
	li $a0, 10
	li $v0, 11
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
	lw $sp, -184($v0)
	lw $zero, g_x($t8)
	sw $sp, -188($t8)
	lw $sp, -188($t8)
	seq $v1, $t8, 5
	sw $sp, -192($v1)
	lw $sp, -192($t8)
	beq $t8, $zero, func_main_block_98
	j func_main_block_92
func_main_block_92:
	addu $fp, $sp, $zero
	addi $sp, $sp, -192
	jal func_f2
	addi $sp, $sp, 192
	lw $sp, -196($v0)
	lw $sp, -196($t8)
	seq $v1, $t8, -1
	sw $sp, -200($v1)
	lw $sp, -200($t8)
	beq $t8, $zero, func_main_block_97
	j func_main_block_95
func_main_block_95:
	la $t8, g_dqr3($zero)
	sw $sp, -204($t8)
	la $a0, g_dqr3($zero)
	li $v0, 4
	syscall
	li $a0, 10
	li $v0, 11
	syscall
	j func_main_block_97
func_main_block_97:
	j func_main_block_98
func_main_block_98:
	la $t8, g_dqr4($zero)
	sw $sp, -208($t8)
	la $a0, g_dqr4($zero)
	li $v0, 4
	syscall
	li $a0, 10
	li $v0, 11
	syscall
	li $t8, -1
	sw $zero, g_x($t8)
	li $t8, 0
	sw $sp, -12($t8)
	j func_main_block_100
func_main_block_100:
	lw $sp, -12($t8)
	sw $sp, -212($t8)
	lw $sp, -12($t8)
	sw $sp, -216($t8)
	lw $sp, -212($t8)
	lw $sp, -216($t9)
	mul $v1, $t8, $t9
	sw $sp, -220($v1)
	lw $sp, -16($t8)
	sw $sp, -224($t8)
	lw $sp, -16($t8)
	sw $sp, -228($t8)
	lw $sp, -224($t8)
	lw $sp, -228($t9)
	mul $v1, $t8, $t9
	sw $sp, -232($v1)
	lw $sp, -220($t8)
	lw $sp, -232($t9)
	slt $v1, $t8, $t9
	sw $sp, -236($v1)
	lw $sp, -236($t8)
	beq $t8, $zero, func_main_block_127
	j func_main_block_108
func_main_block_108:
	li $v0, 5
	syscall
	sw $sp, -240($v0)
	lw $sp, -240($t8)
	sw $sp, -20($t8)
	lw $sp, -20($t8)
	sw $sp, -244($t8)
	addu $fp, $sp, $zero
	addi $sp, $sp, -248
	lw $sp, -244($a0)
	jal func_f4
	addi $sp, $sp, 248
	lw $sp, -248($v0)
	addu $fp, $sp, $zero
	addi $sp, $sp, -252
	lw $sp, -248($a0)
	jal func_f3
	addi $sp, $sp, 252
	lw $sp, -252($v0)
	lw $zero, g_x($t8)
	sw $sp, -256($t8)
	lw $sp, -256($t8)
	slti $v1, $t8, 0
	sw $sp, -260($v1)
	lw $sp, -260($t8)
	beq $t8, $zero, func_main_block_116
	j func_main_block_114
func_main_block_114:
	j func_main_block_127
func_main_block_115:
	j func_main_block_116
func_main_block_116:
	lw $zero, g_x($t8)
	sw $sp, -264($t8)
	lw $sp, -264($t8)
	sgt $v1, $t8, 0
	sw $sp, -268($v1)
	lw $sp, -268($t8)
	beq $t8, $zero, func_main_block_121
	j func_main_block_119
func_main_block_119:
	j func_main_block_124
func_main_block_120:
	j func_main_block_121
func_main_block_121:
	lw $sp, -12($t8)
	sw $sp, -272($t8)
	lw $sp, -272($t8)
	addiu $v1, $t8, 1
	sw $sp, -276($v1)
	lw $sp, -276($t8)
	sw $sp, -12($t8)
	j func_main_block_124
func_main_block_124:
	lw $sp, -12($t8)
	sw $sp, -280($t8)
	lw $sp, -280($t8)
	addiu $v1, $t8, 1
	sw $sp, -284($v1)
	lw $sp, -284($t8)
	sw $sp, -12($t8)
	j func_main_block_100
func_main_block_127:
	lw $zero, g_x($t8)
	sw $sp, -288($t8)
	lw $sp, -288($t8)
	sge $v1, $t8, 0
	sw $sp, -292($v1)
	lw $sp, -292($t8)
	beq $t8, $zero, func_main_block_132
	j func_main_block_130
func_main_block_130:
	la $t8, g_dqr5($zero)
	sw $sp, -296($t8)
	la $a0, g_dqr5($zero)
	li $v0, 4
	syscall
	li $a0, 10
	li $v0, 11
	syscall
	j func_main_block_132
func_main_block_132:
	li $t8, 10
	sw $sp, -12($t8)
	li $t8, 5
	sw $sp, -16($t8)
	li $t8, 7
	sw $sp, -20($t8)
	lw $sp, -12($t8)
	sw $sp, -300($t8)
	lw $sp, -16($t8)
	sw $sp, -304($t8)
	lw $sp, -20($t8)
	sw $sp, -308($t8)
	addu $fp, $sp, $zero
	addi $sp, $sp, -320
	lw $sp, -300($a0)
	lw $sp, -304($a1)
	lw $sp, -308($a2)
	jal func_f5
	addi $sp, $sp, 320
	lw $sp, -312($v0)
	lw $sp, -12($t8)
	sw $sp, -316($t8)
	lw $sp, -312($t8)
	lw $sp, -316($t9)
	seq $v1, $t8, $t9
	sw $sp, -320($v1)
	lw $sp, -320($t8)
	beq $t8, $zero, func_main_block_141
	j func_main_block_139
func_main_block_139:
	la $t8, g_dqr6($zero)
	sw $sp, -324($t8)
	la $a0, g_dqr6($zero)
	li $v0, 4
	syscall
	li $a0, 10
	li $v0, 11
	syscall
	j func_main_block_141
func_main_block_141:
	li $t8, 0
	sw $zero, g_x($t8)
	addu $fp, $sp, $zero
	addi $sp, $sp, -328
	li $a0, 10
	jal func_f6
	addi $sp, $sp, 328
	lw $sp, -328($v0)
	lw $zero, g_x($t8)
	sw $sp, -332($t8)
	la $t8, g_dqr7($zero)
	sw $sp, -336($t8)
	la $a0, g_dqr7($zero)
	li $v0, 4
	syscall
	lw $sp, -332($a0)
	li $v0, 1
	syscall
	li $a0, 10
	li $v0, 11
	syscall
	la $t8, g_dqr8($zero)
	sw $sp, -340($t8)
	la $a0, g_dqr8($zero)
	li $v0, 4
	syscall
	li $a0, 10
	li $v0, 11
	syscall
	la $t8, g_dqr9($zero)
	sw $sp, -344($t8)
	la $a0, g_dqr9($zero)
	li $v0, 4
	syscall
	li $v0, 0
	lw $sp, -4($ra)
	jr $ra
