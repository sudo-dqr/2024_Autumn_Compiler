.data
	g_dqr0: .asciiz "Sun Mon Tue Wed Thu Fri Sat\n"
	g_dqr1: .asciiz "    "
	g_dqr2: .asciiz "  "
	g_dqr3: .asciiz "\n"
	g_dqr4: .asciiz "\n"


.text
	jal func_main
	li $v0, 10
	syscall

func_is_leap_year:
	sw $ra, -4($sp)
func_is_leap_year_block_1:
	sw $a0, -8($sp)
	lw $t0, -8($sp)
	rem $t1, $t0, 400
	seq $t2, $t1, 0
	beq $t2, $zero, func_is_leap_year_block_8
	j func_is_leap_year_block_6
func_is_leap_year_block_6:
	li $v0, 1
	lw $ra, -4($sp)
	jr $ra
func_is_leap_year_block_7:
	j func_is_leap_year_block_21
func_is_leap_year_block_8:
	lw $t0, -8($sp)
	andi $t1, $t0, 3
	bgez $t0, rem_opt_0
	beq $t1, $zero, rem_opt_0
	addiu $t1, $t1, -4
rem_opt_0:
	seq $t2, $t1, 0
	beq $t2, $zero, func_is_leap_year_block_18
	j func_is_leap_year_block_12
func_is_leap_year_block_12:
	lw $t0, -8($sp)
	rem $t1, $t0, 100
	sne $t2, $t1, 0
	beq $t2, $zero, func_is_leap_year_block_18
	j func_is_leap_year_block_16
func_is_leap_year_block_16:
	li $v0, 1
	lw $ra, -4($sp)
	jr $ra
func_is_leap_year_block_17:
	j func_is_leap_year_block_20
func_is_leap_year_block_18:
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
func_is_leap_year_block_19:
	j func_is_leap_year_block_20
func_is_leap_year_block_20:
	j func_is_leap_year_block_21
func_is_leap_year_block_21:
func_zeller:
	sw $ra, -4($sp)
func_zeller_block_3:
	sw $a0, -8($sp)
	sw $a1, -12($sp)
	sw $a2, -16($sp)
	lw $t0, -12($sp)
	slti $t1, $t0, 3
	beq $t1, $zero, func_zeller_block_14
	j func_zeller_block_9
func_zeller_block_9:
	lw $t0, -12($sp)
	addiu $t1, $t0, 12
	sw $t1, -12($sp)
	lw $t2, -16($sp)
	addiu $t3, $t2, -1
	sw $t3, -16($sp)
	j func_zeller_block_14
func_zeller_block_14:
	lw $t0, -16($sp)
	rem $t1, $t0, 100
	sw $t1, -32($sp)
	lw $t2, -16($sp)
	li $k0, 1374389535
	mult $k0, $t2
	mfhi $k0
	sra $k0, $k0, 5
	sra $k1, $t2, 31
	subu $t3, $k0, $k1
	sw $t3, -36($sp)
	lw $t4, -8($sp)
	lw $t5, -12($sp)
	addiu $t6, $t5, 1
	mul $t7, $t6, 13
	li $k0, 1717986919
	mult $k0, $t7
	mfhi $k0
	sra $k0, $k0, 1
	sra $k1, $t7, 31
	subu $s0, $k0, $k1
	addu $s1, $t4, $s0
	lw $s2, -32($sp)
	addu $s3, $s1, $s2
	lw $s4, -32($sp)
	sra $k0, $s4, 1
	srl $k0, $k0, 30
	addu $k0, $k0, $s4
	sra $s5, $k0, 2
	addu $s6, $s3, $s5
	lw $s7, -36($sp)
	sra $k0, $s7, 1
	srl $k0, $k0, 30
	addu $k0, $k0, $s7
	sra $v1, $k0, 2
	sw $v1, -44($sp)
	lw $t9, -44($sp)
	addu $v1, $s6, $t9
	sw $v1, -48($sp)
	lw $v1, -36($sp)
	sw $v1, -52($sp)
	lw $t9, -52($sp)
	mul $v1, $t9, 5
	sw $v1, -56($sp)
	lw $t8, -48($sp)
	lw $t9, -56($sp)
	addu $v1, $t8, $t9
	sw $v1, -60($sp)
	lw $t8, -60($sp)
	rem $v1, $t8, 7
	sw $v1, -64($sp)
	lw $t8, -64($sp)
	sw $t8, -40($sp)
	lw $v1, -40($sp)
	sw $v1, -68($sp)
	lw $t8, -68($sp)
	addiu $v1, $t8, 5
	sw $v1, -72($sp)
	lw $t8, -72($sp)
	rem $v1, $t8, 7
	sw $v1, -76($sp)
	lw $v0, -76($sp)
	lw $ra, -4($sp)
	jr $ra
func_zeller_block_43:
func_calendar:
	sw $ra, -4($sp)
func_calendar_block_2:
	sw $a0, -8($sp)
	sw $a1, -12($sp)
	la $t8, -84($sp)
	addu $t0, $t8, $zero
	li $t8, 31
	sw $t8, 0($t0)
	la $t8, -84($sp)
	addiu $t8, $t8, 4
	addu $t1, $t8, $zero
	li $t8, 28
	sw $t8, 0($t1)
	la $t8, -84($sp)
	addiu $t8, $t8, 8
	addu $t2, $t8, $zero
	li $t8, 31
	sw $t8, 0($t2)
	la $t8, -84($sp)
	addiu $t8, $t8, 12
	addu $t3, $t8, $zero
	li $t8, 30
	sw $t8, 0($t3)
	la $t8, -84($sp)
	addiu $t8, $t8, 16
	addu $t4, $t8, $zero
	li $t8, 31
	sw $t8, 0($t4)
	la $t8, -84($sp)
	addiu $t8, $t8, 20
	addu $t5, $t8, $zero
	li $t8, 30
	sw $t8, 0($t5)
	la $t8, -84($sp)
	addiu $t8, $t8, 24
	addu $t6, $t8, $zero
	li $t8, 31
	sw $t8, 0($t6)
	la $t8, -84($sp)
	addiu $t8, $t8, 28
	addu $t7, $t8, $zero
	li $t8, 31
	sw $t8, 0($t7)
	la $t8, -84($sp)
	addiu $t8, $t8, 32
	addu $s0, $t8, $zero
	li $t8, 30
	sw $t8, 0($s0)
	la $t8, -84($sp)
	addiu $t8, $t8, 36
	addu $s1, $t8, $zero
	li $t8, 31
	sw $t8, 0($s1)
	la $t8, -84($sp)
	addiu $t8, $t8, 40
	addu $s2, $t8, $zero
	li $t8, 30
	sw $t8, 0($s2)
	la $t8, -84($sp)
	addiu $t8, $t8, 44
	addu $s3, $t8, $zero
	li $t8, 31
	sw $t8, 0($s3)
	lw $s4, -8($sp)
	sw $s3, -92($sp)
	sw $s2, -96($sp)
	sw $s1, -100($sp)
	sw $s0, -104($sp)
	sw $t7, -108($sp)
	sw $t6, -112($sp)
	sw $t5, -116($sp)
	sw $t4, -120($sp)
	sw $t3, -124($sp)
	sw $t2, -128($sp)
	sw $t1, -132($sp)
	sw $t0, -136($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -140
	addu $a0, $s4, $zero
	jal func_is_leap_year
	addiu $sp, $sp, 140
	lw $t0, -136($sp)
	lw $t1, -132($sp)
	lw $t2, -128($sp)
	lw $t3, -124($sp)
	lw $t4, -120($sp)
	lw $t5, -116($sp)
	lw $t6, -112($sp)
	lw $t7, -108($sp)
	lw $s0, -104($sp)
	lw $s1, -100($sp)
	lw $s2, -96($sp)
	lw $s3, -92($sp)
	lw $s4, -88($sp)
	addu $s5, $v0, $zero
	sne $s6, $s5, 0
	beq $s6, $zero, func_calendar_block_27
	j func_calendar_block_22
func_calendar_block_22:
	lw $t0, -12($sp)
	seq $t1, $t0, 2
	beq $t1, $zero, func_calendar_block_27
	j func_calendar_block_25
func_calendar_block_25:
	la $t8, -84($sp)
	addiu $t8, $t8, 4
	addu $t0, $t8, $zero
	li $t8, 29
	sw $t8, 0($t0)
	j func_calendar_block_27
func_calendar_block_27:
	lw $t0, -12($sp)
	lw $t1, -8($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -108
	li $a0, 1
	addu $a1, $t0, $zero
	addu $a2, $t1, $zero
	jal func_zeller
	addiu $sp, $sp, 108
	lw $t0, -96($sp)
	lw $t1, -92($sp)
	addu $t2, $v0, $zero
	sw $t2, -88($sp)
	la $t8, g_dqr0($zero)
	addu $t3, $t8, $zero
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	li $t8, 0
	sw $t8, -24($sp)
	j func_calendar_block_33
func_calendar_block_33:
	lw $t0, -24($sp)
	lw $t1, -88($sp)
	slt $t2, $t0, $t1
	beq $t2, $zero, func_calendar_block_42
	j func_calendar_block_37
func_calendar_block_37:
	la $t8, g_dqr1($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	j func_calendar_block_39
func_calendar_block_39:
	lw $t0, -24($sp)
	addiu $t1, $t0, 1
	sw $t1, -24($sp)
	j func_calendar_block_33
func_calendar_block_42:
	li $t8, 1
	sw $t8, -92($sp)
	lw $t0, -88($sp)
	sw $t0, -96($sp)
	j func_calendar_block_46
func_calendar_block_46:
	lw $t0, -92($sp)
	lw $t1, -12($sp)
	addiu $t2, $t1, -1
	la $t8, -84($sp)
	sll $t2, $t2, 2
	addu $t8, $t8, $t2
	addu $t3, $t8, $zero
	lw $t4, 0($t3)
	sle $t5, $t0, $t4
	beq $t5, $zero, func_calendar_block_72
	j func_calendar_block_53
func_calendar_block_53:
	lw $t0, -92($sp)
	slti $t1, $t0, 10
	beq $t1, $zero, func_calendar_block_59
	j func_calendar_block_56
func_calendar_block_56:
	lw $t0, -92($sp)
	la $t8, g_dqr2($zero)
	addu $t1, $t8, $zero
	la $a0, g_dqr2($zero)
	li $v0, 4
	syscall
	addu $a0, $t0, $zero
	li $v0, 1
	syscall
	li $a0, 32
	li $v0, 11
	syscall
	j func_calendar_block_61
func_calendar_block_59:
	lw $t0, -92($sp)
	li $a0, 32
	li $v0, 11
	syscall
	addu $a0, $t0, $zero
	li $v0, 1
	syscall
	li $a0, 32
	li $v0, 11
	syscall
	j func_calendar_block_61
func_calendar_block_61:
	lw $t0, -96($sp)
	rem $t1, $t0, 7
	seq $t2, $t1, 6
	beq $t2, $zero, func_calendar_block_67
	j func_calendar_block_65
func_calendar_block_65:
	la $t8, g_dqr3($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr3($zero)
	li $v0, 4
	syscall
	j func_calendar_block_67
func_calendar_block_67:
	lw $t0, -92($sp)
	addiu $t1, $t0, 1
	sw $t1, -92($sp)
	lw $t2, -96($sp)
	addiu $t3, $t2, 1
	sw $t3, -96($sp)
	j func_calendar_block_46
func_calendar_block_72:
	lw $t0, -88($sp)
	lw $t1, -12($sp)
	addiu $t2, $t1, -1
	la $t8, -84($sp)
	sll $t2, $t2, 2
	addu $t8, $t8, $t2
	addu $t3, $t8, $zero
	lw $t4, 0($t3)
	addu $t5, $t0, $t4
	rem $t6, $t5, 7
	sne $t7, $t6, 0
	beq $t7, $zero, func_calendar_block_83
	j func_calendar_block_81
func_calendar_block_81:
	la $t8, g_dqr4($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr4($zero)
	li $v0, 4
	syscall
	j func_calendar_block_83
func_calendar_block_83:
	lw $ra, -4($sp)
	jr $ra
func_main:
	sw $ra, -4($sp)
func_main_block_0:
	li $v0, 5
	syscall
	addu $t0, $v0, $zero
	sw $t0, -8($sp)
	li $v0, 5
	syscall
	addu $t1, $v0, $zero
	sw $t1, -12($sp)
	lw $t2, -8($sp)
	lw $t3, -12($sp)
	sw $t1, -24($sp)
	sw $t0, -28($sp)
	addu $fp, $sp, $zero
	addiu $sp, $sp, -36
	addu $a0, $t2, $zero
	addu $a1, $t3, $zero
	jal func_calendar
	addiu $sp, $sp, 36
	lw $t0, -28($sp)
	lw $t1, -24($sp)
	lw $t2, -20($sp)
	lw $t3, -16($sp)
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
func_main_block_7:
