.data
	g_singleVarDecl: .word -10
	g_singleVarDecl_0: .word 23
	g_singleVarDecl_1: .word 10
	g_singleVarDecl_2: .word 0
	g_dqr0: .asciiz "print int : "
	g_dqr1: .asciiz "\n"
	g_dqr2: .asciiz "19373479\n"


.text
	jal func_main
	li $v0, 10
	syscall

func_funcDef_void:
	sw $ra, -4($sp)
func_funcDef_void_block_0:
	lw $ra, -4($sp)
	jr $ra
func_funcDef_0:
	sw $ra, -4($sp)
func_funcDef_0_block_1:
	sw $a0, -8($sp)
	lw $t8, -8($sp)
	sw $t8, -20($sp)
	lw $t8, -20($sp)
	mul $v1, $t8, 10
	sw $v1, -24($sp)
	lw $t8, -24($sp)
	sw $t8, -16($sp)
	lw $t8, -16($sp)
	sw $t8, -28($sp)
	lw $v0, -28($sp)
	lw $ra, -4($sp)
	jr $ra
func_funcDef_1:
	sw $ra, -4($sp)
func_funcDef_1_block_2:
	sw $a0, -8($sp)
	sw $a1, -12($sp)
	lw $t8, -8($sp)
	sw $t8, -28($sp)
	lw $t8, -12($sp)
	sw $t8, -32($sp)
	lw $t8, -28($sp)
	lw $t9, -32($sp)
	mul $v1, $t8, $t9
	sw $v1, -36($sp)
	lw $t8, -36($sp)
	sw $t8, -24($sp)
	lw $t8, -12($sp)
	sw $t8, -48($sp)
	lw $t8, -48($sp)
	sne $v1, $t8, 0
	sw $v1, -52($sp)
	lw $t8, -52($sp)
	beq $t8, $zero, func_funcDef_1_block_22
	j func_funcDef_1_block_13
func_funcDef_1_block_13:
	lw $t8, -24($sp)
	sw $t8, -56($sp)
	lw $t8, -8($sp)
	sw $t8, -60($sp)
	lw $t8, -12($sp)
	sw $t8, -64($sp)
	lw $t8, -60($sp)
	lw $t9, -64($sp)
	rem $v1, $t8, $t9
	sw $v1, -68($sp)
	lw $t8, -56($sp)
	lw $t9, -68($sp)
	addu $v1, $t8, $t9
	sw $v1, -72($sp)
	lw $t8, -72($sp)
	sw $t8, -40($sp)
	lw $t8, -8($sp)
	sw $t8, -76($sp)
	lw $t8, -12($sp)
	sw $t8, -80($sp)
	lw $t8, -76($sp)
	lw $t9, -80($sp)
	div $v1, $t8, $t9
	sw $v1, -84($sp)
	lw $t8, -84($sp)
	sw $t8, -44($sp)
	j func_funcDef_1_block_28
func_funcDef_1_block_22:
	lw $t8, -24($sp)
	sw $t8, -88($sp)
	lw $t8, -8($sp)
	sw $t8, -92($sp)
	lw $t8, -88($sp)
	lw $t9, -92($sp)
	addu $v1, $t8, $t9
	sw $v1, -96($sp)
	lw $t8, -96($sp)
	sw $t8, -40($sp)
	lw $t8, -8($sp)
	sw $t8, -100($sp)
	lw $t8, -100($sp)
	div $v1, $t8, 2
	sw $v1, -104($sp)
	lw $t8, -104($sp)
	sw $t8, -44($sp)
	j func_funcDef_1_block_28
func_funcDef_1_block_28:
	lw $t8, -40($sp)
	sw $t8, -108($sp)
	lw $t8, -24($sp)
	sw $t8, -112($sp)
	lw $t8, -108($sp)
	lw $t9, -112($sp)
	subu $v1, $t8, $t9
	sw $v1, -116($sp)
	lw $t8, -116($sp)
	sw $t8, -40($sp)
	lw $t8, -24($sp)
	sw $t8, -120($sp)
	lw $t8, -40($sp)
	sw $t8, -124($sp)
	lw $t8, -120($sp)
	lw $t9, -124($sp)
	addu $v1, $t8, $t9
	sw $v1, -128($sp)
	lw $t8, -24($sp)
	sw $t8, -132($sp)
	lw $t8, -132($sp)
	slti $v1, $t8, 0
	sw $v1, -136($sp)
	lw $t8, -136($sp)
	beq $t8, $zero, func_funcDef_1_block_40
	j func_funcDef_1_block_37
func_funcDef_1_block_37:
	lw $t8, -24($sp)
	sw $t8, -140($sp)
	lw $t9, -140($sp)
	li $t8, 0
	subu $v1, $t8, $t9
	sw $v1, -144($sp)
	lw $t8, -144($sp)
	sw $t8, -24($sp)
	j func_funcDef_1_block_40
func_funcDef_1_block_40:
	lw $t8, -24($sp)
	sw $t8, -148($sp)
	lw $t9, -148($sp)
	addiu $v1, $t9, 1
	sw $v1, -152($sp)
	lw $t8, -40($sp)
	sw $t8, -156($sp)
	lw $t8, -44($sp)
	sw $t8, -160($sp)
	lw $t8, -156($sp)
	lw $t9, -160($sp)
	addu $v1, $t8, $t9
	sw $v1, -164($sp)
	lw $t8, -152($sp)
	lw $t9, -164($sp)
	mul $v1, $t8, $t9
	sw $v1, -168($sp)
	lw $v0, -168($sp)
	lw $ra, -4($sp)
	jr $ra
func_printInt:
	sw $ra, -4($sp)
func_printInt_block_1:
	sw $a0, -8($sp)
	lw $t8, -8($sp)
	sw $t8, -16($sp)
	la $t8, g_dqr0($zero)
	sw $t8, -20($sp)
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	lw $a0, -16($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr1($zero)
	sw $t8, -24($sp)
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	lw $ra, -4($sp)
	jr $ra
func_main:
	sw $ra, -4($sp)
func_main_block_0:
	la $t8, g_dqr2($zero)
	sw $t8, -8($sp)
	la $a0, g_dqr2($zero)
	li $v0, 4
	syscall
	li $t8, 10
	sw $t8, -12($sp)
	li $v0, 5
	syscall
	sw $v0, -32($sp)
	lw $t8, -32($sp)
	sw $t8, -16($sp)
	li $v0, 5
	syscall
	sw $v0, -36($sp)
	lw $t8, -36($sp)
	sw $t8, -20($sp)
	li $v0, 5
	syscall
	sw $v0, -40($sp)
	lw $t8, -40($sp)
	sw $t8, -24($sp)
	li $v0, 5
	syscall
	sw $v0, -44($sp)
	lw $t8, -44($sp)
	sw $t8, -28($sp)
	lw $t8, -16($sp)
	sw $t8, -48($sp)
	lw $t8, -48($sp)
	sgt $v1, $t8, 5
	sw $v1, -52($sp)
	lw $t8, -52($sp)
	beq $t8, $zero, func_main_block_14
	j func_main_block_13
func_main_block_13:
	li $t8, 5
	sw $t8, -16($sp)
	j func_main_block_14
func_main_block_14:
	j func_main_block_15
func_main_block_15:
	lw $t8, -12($sp)
	sw $t8, -56($sp)
	lw $t8, -56($sp)
	sne $v1, $t8, 0
	sw $v1, -60($sp)
	lw $t8, -60($sp)
	beq $t8, $zero, func_main_block_69
	j func_main_block_18
func_main_block_18:
	lw $t8, -12($sp)
	sw $t8, -64($sp)
	lw $t8, -64($sp)
	subu $v1, $t8, 1
	sw $v1, -68($sp)
	lw $t8, -68($sp)
	sw $t8, -12($sp)
	lw $t8, -20($sp)
	sw $t8, -72($sp)
	lw $t8, -12($sp)
	sw $t8, -76($sp)
	lw $t8, -72($sp)
	lw $t9, -76($sp)
	sge $v1, $t8, $t9
	sw $v1, -80($sp)
	lw $t8, -80($sp)
	beq $t8, $zero, func_main_block_31
	j func_main_block_24
func_main_block_24:
	lw $t8, -20($sp)
	sw $t8, -84($sp)
	lw $t8, -12($sp)
	sw $t8, -88($sp)
	lw $t8, -88($sp)
	addiu $v1, $t8, 1
	sw $v1, -92($sp)
	lw $t8, -84($sp)
	lw $t9, -92($sp)
	div $v1, $t8, $t9
	sw $v1, -96($sp)
	lw $t8, -12($sp)
	sw $t8, -100($sp)
	lw $t8, -96($sp)
	lw $t9, -100($sp)
	addu $v1, $t8, $t9
	sw $v1, -104($sp)
	lw $t8, -104($sp)
	sw $t8, -20($sp)
	j func_main_block_31
func_main_block_31:
	lw $t8, -24($sp)
	sw $t8, -108($sp)
	lw $t8, -12($sp)
	sw $t8, -112($sp)
	lw $t8, -108($sp)
	lw $t9, -112($sp)
	sle $v1, $t8, $t9
	sw $v1, -116($sp)
	lw $t8, -116($sp)
	beq $t8, $zero, func_main_block_39
	j func_main_block_35
func_main_block_35:
	lw $t8, -24($sp)
	sw $t8, -120($sp)
	lw $t8, -12($sp)
	sw $t8, -124($sp)
	lw $t8, -120($sp)
	lw $t9, -124($sp)
	mul $v1, $t8, $t9
	sw $v1, -128($sp)
	lw $t8, -128($sp)
	sw $t8, -24($sp)
	j func_main_block_44
func_main_block_39:
	lw $t8, -24($sp)
	sw $t8, -132($sp)
	lw $t8, -12($sp)
	sw $t8, -136($sp)
	lw $t8, -136($sp)
	addiu $v1, $t8, 3
	sw $v1, -140($sp)
	lw $t8, -132($sp)
	lw $t9, -140($sp)
	rem $v1, $t8, $t9
	sw $v1, -144($sp)
	lw $t8, -144($sp)
	sw $t8, -24($sp)
	j func_main_block_44
func_main_block_44:
	j func_main_block_45
func_main_block_45:
	lw $t8, -28($sp)
	sw $t8, -148($sp)
	lw $t8, -24($sp)
	sw $t8, -152($sp)
	lw $t8, -148($sp)
	lw $t9, -152($sp)
	slt $v1, $t8, $t9
	sw $v1, -156($sp)
	lw $t8, -156($sp)
	beq $t8, $zero, func_main_block_68
	j func_main_block_49
func_main_block_49:
	lw $t8, -28($sp)
	sw $t8, -160($sp)
	lw $t8, -12($sp)
	sw $t8, -164($sp)
	lw $t8, -160($sp)
	lw $t9, -164($sp)
	addu $v1, $t8, $t9
	sw $v1, -168($sp)
	lw $t8, -168($sp)
	sw $t8, -28($sp)
	lw $t8, -28($sp)
	sw $t8, -172($sp)
	lw $t8, -16($sp)
	sw $t8, -176($sp)
	lw $t8, -172($sp)
	lw $t9, -176($sp)
	seq $v1, $t8, $t9
	sw $v1, -180($sp)
	lw $t8, -180($sp)
	beq $t8, $zero, func_main_block_58
	j func_main_block_56
func_main_block_56:
	j func_main_block_68
func_main_block_57:
	j func_main_block_58
func_main_block_58:
	lw $t8, -28($sp)
	sw $t8, -184($sp)
	lw $t8, -20($sp)
	sw $t8, -188($sp)
	lw $t8, -184($sp)
	lw $t9, -188($sp)
	sne $v1, $t8, $t9
	sw $v1, -192($sp)
	lw $t8, -192($sp)
	beq $t8, $zero, func_main_block_67
	j func_main_block_62
func_main_block_62:
	lw $t8, -20($sp)
	sw $t8, -196($sp)
	lw $t8, -28($sp)
	sw $t8, -200($sp)
	lw $t8, -196($sp)
	lw $t9, -200($sp)
	addu $v1, $t8, $t9
	sw $v1, -204($sp)
	lw $t8, -204($sp)
	sw $t8, -28($sp)
	j func_main_block_45
func_main_block_66:
	j func_main_block_67
func_main_block_67:
	j func_main_block_45
func_main_block_68:
	j func_main_block_15
func_main_block_69:
	lw $t8, -12($sp)
	sw $t8, -208($sp)
	lw $t8, -208($sp)
	seq $v1, $t8, 0
	sw $v1, -212($sp)
	lw $t8, -212($sp)
	sne $v1, $t8, 0
	sw $v1, -216($sp)
	lw $t8, -216($sp)
	beq $t8, $zero, func_main_block_76
	j func_main_block_74
func_main_block_74:
	lw $t8, -12($sp)
	sw $t8, -220($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -224
	lw $a0, -220($fp)
	jal func_printInt
	addi $sp, $sp, 224
	sw $v0, -224($sp)
	j func_main_block_76
func_main_block_76:
	lw $t8, -16($sp)
	sw $t8, -228($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -232
	lw $a0, -228($fp)
	jal func_printInt
	addi $sp, $sp, 232
	sw $v0, -232($sp)
	lw $t8, -20($sp)
	sw $t8, -236($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -240
	lw $a0, -236($fp)
	jal func_printInt
	addi $sp, $sp, 240
	sw $v0, -240($sp)
	lw $t8, -24($sp)
	sw $t8, -244($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -248
	lw $a0, -244($fp)
	jal func_printInt
	addi $sp, $sp, 248
	sw $v0, -248($sp)
	lw $t8, -28($sp)
	sw $t8, -252($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -256
	lw $a0, -252($fp)
	jal func_printInt
	addi $sp, $sp, 256
	sw $v0, -256($sp)
	lw $t8, -28($sp)
	sw $t8, -264($sp)
	lw $t8, -24($sp)
	sw $t8, -268($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -276
	lw $a0, -264($fp)
	lw $a1, -268($fp)
	jal func_funcDef_1
	addi $sp, $sp, 276
	sw $v0, -272($sp)
	lw $t8, -272($sp)
	sw $t8, -260($sp)
	lw $t8, -260($sp)
	sw $t8, -280($sp)
	lw $t8, -20($sp)
	sw $t8, -284($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -288
	lw $a0, -284($fp)
	jal func_funcDef_0
	addi $sp, $sp, 288
	sw $v0, -288($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -296
	lw $a0, -280($fp)
	lw $a1, -288($fp)
	jal func_funcDef_1
	addi $sp, $sp, 296
	sw $v0, -292($sp)
	lw $t8, -292($sp)
	sw $t8, -276($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -292
	jal func_funcDef_void
	addi $sp, $sp, 292
	sw $v0, -296($sp)
	lw $t8, -260($sp)
	sw $t8, -300($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -304
	lw $a0, -300($fp)
	jal func_printInt
	addi $sp, $sp, 304
	sw $v0, -304($sp)
	lw $t8, -276($sp)
	sw $t8, -308($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -312
	lw $a0, -308($fp)
	jal func_printInt
	addi $sp, $sp, 312
	sw $v0, -312($sp)
	lw $t8, g_singleVarDecl($zero)
	sw $t8, -316($sp)
	lw $t8, g_singleVarDecl_2($zero)
	sw $t8, -320($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -328
	lw $a0, -316($fp)
	lw $a1, -320($fp)
	jal func_funcDef_1
	addi $sp, $sp, 328
	sw $v0, -324($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -332
	li $a0, 13
	li $a1, 3
	jal func_funcDef_1
	addi $sp, $sp, 332
	sw $v0, -328($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -336
	lw $a0, -324($fp)
	lw $a1, -328($fp)
	jal func_funcDef_1
	addi $sp, $sp, 336
	sw $v0, -332($sp)
	lw $t8, -332($sp)
	sw $t8, g_singleVarDecl_2($zero)
	lw $t8, g_singleVarDecl_2($zero)
	sw $t8, -336($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -340
	lw $a0, -336($fp)
	jal func_printInt
	addi $sp, $sp, 340
	sw $v0, -340($sp)
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
