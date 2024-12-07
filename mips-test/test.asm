.data
	g_varInt: .word 0
	g_varIntB: .word 5
	g_varIntC: .word 15
	g_varChar: .byte 0
	g_dqr0: .asciiz "Function with no parameters\n"
	g_dqr1: .asciiz "Function with single parameter, x = "
	g_dqr2: .asciiz "\n"
	g_dqr3: .asciiz "Function with parameters: a = "
	g_dqr4: .asciiz ", b = "
	g_dqr5: .asciiz "\n"
	g_dqr6: .asciiz "Function returning a character\n"
	g_dqr7: .asciiz "22373141\n"
	g_dqr8: .asciiz "Result of functionWithParams: "
	g_dqr9: .asciiz "\n"
	g_dqr10: .asciiz "Character returned: "
	g_dqr11: .asciiz "\n"
	g_dqr12: .asciiz "Result of functionSingleParam: "
	g_dqr13: .asciiz "\n"
	g_dqr14: .asciiz "Input integer: "
	g_dqr15: .asciiz "\n"
	g_dqr16: .asciiz "Input character: "
	g_dqr17: .asciiz "\n"


.text
	jal func_main
	li $v0, 10
	syscall

func_functionNoParam:
	sw $ra, -4($sp)
func_functionNoParam_block_0:
	la $t8, g_dqr0($zero)
	sw $t8, -8($sp)
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	lw $ra, -4($sp)
	jr $ra
func_functionSingleParam:
	sw $ra, -4($sp)
func_functionSingleParam_block_1:
	sw $a0, -8($sp)
	lw $t8, -8($sp)
	sw $t8, -16($sp)
	la $t8, g_dqr1($zero)
	sw $t8, -20($sp)
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	lw $a0, -16($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr2($zero)
	sw $t8, -24($sp)
	la $a0, g_dqr2($zero)
	li $v0, 4
	syscall
	lw $t8, -8($sp)
	sw $t8, -28($sp)
	lw $t8, -8($sp)
	sw $t8, -32($sp)
	lw $t8, -28($sp)
	lw $t9, -32($sp)
	subu $v1, $t8, $t9
	sw $v1, -36($sp)
	lw $t8, -36($sp)
	addiu $v1, $t8, 8
	sw $v1, -40($sp)
	lw $v0, -40($sp)
	lw $ra, -4($sp)
	jr $ra
func_functionWithParams:
	sw $ra, -4($sp)
func_functionWithParams_block_2:
	sw $a0, -8($sp)
	sw $a1, -12($sp)
	lw $t8, -8($sp)
	sw $t8, -24($sp)
	lbu $t8, -12($sp)
	sw $t8, -28($sp)
	la $t8, g_dqr3($zero)
	sw $t8, -32($sp)
	la $a0, g_dqr3($zero)
	li $v0, 4
	syscall
	lw $a0, -24($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr4($zero)
	sw $t8, -36($sp)
	la $a0, g_dqr4($zero)
	li $v0, 4
	syscall
	lw $a0, -28($sp)
	li $v0, 11
	syscall
	la $t8, g_dqr5($zero)
	sw $t8, -40($sp)
	la $a0, g_dqr5($zero)
	li $v0, 4
	syscall
	lw $t8, -8($sp)
	sw $t8, -44($sp)
	lbu $t8, -12($sp)
	sw $t8, -48($sp)
	lw $t8, -44($sp)
	lw $t9, -48($sp)
	addu $v1, $t8, $t9
	sw $v1, -52($sp)
	lw $v0, -52($sp)
	lw $ra, -4($sp)
	jr $ra
func_functionReturnChar:
	sw $ra, -4($sp)
func_functionReturnChar_block_0:
	la $t8, g_dqr6($zero)
	sw $t8, -8($sp)
	la $a0, g_dqr6($zero)
	li $v0, 4
	syscall
	li $v0, 67
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
	lw $t8, g_varIntB($zero)
	sw $t8, -16($sp)
	lw $t9, -16($sp)
	addiu $v1, $t9, 10
	sw $v1, -20($sp)
	lw $t8, -20($sp)
	sw $t8, -12($sp)
	lw $t8, -12($sp)
	sw $t8, -24($sp)
	lw $t8, g_varIntC($zero)
	sw $t8, -28($sp)
	lw $t8, -24($sp)
	lw $t9, -28($sp)
	mul $v1, $t8, $t9
	sw $v1, -32($sp)
	lw $t8, -32($sp)
	sw $t8, g_varInt($zero)
	li $t8, 65
	sb $t8, g_varChar($zero)
	lw $t8, -12($sp)
	sw $t8, -36($sp)
	lw $t8, g_varInt($zero)
	sw $t8, -40($sp)
	lw $t8, -36($sp)
	lw $t9, -40($sp)
	addu $v1, $t8, $t9
	sw $v1, -44($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -44
	jal func_functionNoParam
	addi $sp, $sp, 44
	sw $v0, -48($sp)
	lw $t8, -12($sp)
	sw $t8, -56($sp)
	lbu $t8, g_varChar($zero)
	sw $t8, -60($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -68
	lw $a0, -56($fp)
	lw $a1, -60($fp)
	jal func_functionWithParams
	addi $sp, $sp, 68
	sw $v0, -64($sp)
	lw $t8, -64($sp)
	sw $t8, -52($sp)
	lw $t8, -52($sp)
	sw $t8, -68($sp)
	la $t8, g_dqr8($zero)
	sw $t8, -72($sp)
	la $a0, g_dqr8($zero)
	li $v0, 4
	syscall
	lw $a0, -68($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr9($zero)
	sw $t8, -76($sp)
	la $a0, g_dqr9($zero)
	li $v0, 4
	syscall
	addu $fp, $sp, $zero
	addi $sp, $sp, -80
	jal func_functionReturnChar
	addi $sp, $sp, 80
	sw $v0, -84($sp)
	lw $t8, -84($sp)
	sb $t8, -80($sp)
	lbu $t8, -80($sp)
	sw $t8, -88($sp)
	la $t8, g_dqr10($zero)
	sw $t8, -92($sp)
	la $a0, g_dqr10($zero)
	li $v0, 4
	syscall
	lw $a0, -88($sp)
	li $v0, 11
	syscall
	la $t8, g_dqr11($zero)
	sw $t8, -96($sp)
	la $a0, g_dqr11($zero)
	li $v0, 4
	syscall
	lw $t8, -12($sp)
	sw $t8, -104($sp)
	addu $fp, $sp, $zero
	addi $sp, $sp, -108
	lw $a0, -104($fp)
	jal func_functionSingleParam
	addi $sp, $sp, 108
	sw $v0, -108($sp)
	lw $t8, -108($sp)
	sw $t8, -100($sp)
	lw $t8, -100($sp)
	sw $t8, -112($sp)
	la $t8, g_dqr12($zero)
	sw $t8, -116($sp)
	la $a0, g_dqr12($zero)
	li $v0, 4
	syscall
	lw $a0, -112($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr13($zero)
	sw $t8, -120($sp)
	la $a0, g_dqr13($zero)
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	sw $v0, -128($sp)
	lw $t8, -128($sp)
	sw $t8, -124($sp)
	lw $t8, -124($sp)
	sw $t8, -132($sp)
	la $t8, g_dqr14($zero)
	sw $t8, -136($sp)
	la $a0, g_dqr14($zero)
	li $v0, 4
	syscall
	lw $a0, -132($sp)
	li $v0, 1
	syscall
	la $t8, g_dqr15($zero)
	sw $t8, -140($sp)
	la $a0, g_dqr15($zero)
	li $v0, 4
	syscall
	li $v0, 12
	syscall
	sw $v0, -148($sp)
	lw $t8, -148($sp)
	sb $t8, -144($sp)
	lbu $t8, -144($sp)
	sw $t8, -152($sp)
	la $t8, g_dqr16($zero)
	sw $t8, -156($sp)
	la $a0, g_dqr16($zero)
	li $v0, 4
	syscall
	lw $a0, -152($sp)
	li $v0, 11
	syscall
	la $t8, g_dqr17($zero)
	sw $t8, -160($sp)
	la $a0, g_dqr17($zero)
	li $v0, 4
	syscall
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
