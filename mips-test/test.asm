.data
	g_x: .word 1
	g_y: .word 2
	g_z: .word 3
	g_a: .word 4
	g_b: .word 5
	g_c: .word 6
	g_d: .word 7
	g_e: .word 8
	g_f: .word 9
	g_g: .word 10
	g_h: .word 11
	g_i: .word 12
	g_j: .word 13
	g_k: .word 14
	g_l: .word 15
	g_m: .word 16
	g_n: .word 17
	g_o: .word 18
	g_p: .word 19
	g_q: .word 20
	g_r: .word 21
	g_s: .word 22
	g_t: .word 23
	g_u: .word 24
	g_v: .word 25
	g_w: .word 26
	g_xx2: .word 27
	g_y2: .word 28
	g_z2: .word 29
	g_aa2: .word 30
	g_b2: .word 31
	g_c2: .word 32
	g_d2: .word 33
	g_e2: .word 34
	g_ff2: .word 35
	g_g2: .word 36
	g_h2: .word 37
	g_i2: .word 38
	g_j2: .word 39
	g_k2: .word 40
	g_dqr0: .asciiz "22371092\n"
	g_dqr1: .asciiz "\n"
	g_dqr2: .asciiz "\n"
	g_dqr3: .asciiz "\n"


.text
	jal func_main
	li $v0, 10
	syscall

func_main:
	sw $ra, -4($sp)
func_main_block_0:
	li $t8, 1
	sw $t8, -8($sp)
	li $t8, 2
	sw $t8, -12($sp)
	li $t8, 3
	sw $t8, -16($sp)
	li $t8, 4
	sw $t8, -20($sp)
	li $t8, 5
	sw $t8, -24($sp)
	li $t8, 6
	sw $t8, -28($sp)
	li $t8, 7
	sw $t8, -32($sp)
	li $t8, 8
	sw $t8, -36($sp)
	li $t8, 9
	sw $t8, -40($sp)
	li $t8, 10
	sw $t8, -44($sp)
	li $t8, 11
	sw $t8, -48($sp)
	li $t8, 12
	sw $t8, -52($sp)
	li $t8, 13
	sw $t8, -56($sp)
	li $t8, 14
	sw $t8, -60($sp)
	li $t8, 15
	sw $t8, -64($sp)
	li $t8, 16
	sw $t8, -68($sp)
	li $t8, 17
	sw $t8, -72($sp)
	li $t8, 18
	sw $t8, -76($sp)
	li $t8, 19
	sw $t8, -80($sp)
	li $t8, 20
	sw $t8, -84($sp)
	li $t8, 21
	sw $t8, -88($sp)
	li $t8, 22
	sw $t8, -92($sp)
	li $t8, 23
	sw $t8, -96($sp)
	li $t8, 24
	sw $t8, -100($sp)
	li $t8, 25
	sw $t8, -104($sp)
	li $t8, 26
	sw $t8, -108($sp)
	li $t8, 27
	sw $t8, -112($sp)
	li $t8, 28
	sw $t8, -116($sp)
	li $t8, 29
	sw $t8, -120($sp)
	li $t8, 30
	sw $t8, -124($sp)
	li $t8, 31
	sw $t8, -128($sp)
	li $t8, 32
	sw $t8, -132($sp)
	li $t8, 33
	sw $t8, -136($sp)
	li $t8, 34
	sw $t8, -140($sp)
	li $t8, 35
	sw $t8, -144($sp)
	li $t8, 36
	sw $t8, -148($sp)
	li $t8, 37
	sw $t8, -152($sp)
	li $t8, 38
	sw $t8, -156($sp)
	li $t8, 39
	sw $t8, -160($sp)
	li $t8, 40
	sw $t8, -164($sp)
	lw $t0, g_x($zero)
	lw $t1, g_y($zero)
	addu $t0, $t0, $t1
	lw $t1, g_z($zero)
	lw $t2, g_a($zero)
	addu $t1, $t1, $t2
	mul $t0, $t0, $t1
	lw $t1, g_b($zero)
	lw $t2, g_c($zero)
	addu $t1, $t1, $t2
	lw $t2, g_d($zero)
	div $t1, $t1, $t2
	subu $t0, $t0, $t1
	sw $t0, g_x($zero)
	lw $t0, g_e($zero)
	lw $t1, g_f($zero)
	mul $t0, $t0, $t1
	lw $t1, g_g($zero)
	addu $t0, $t0, $t1
	lw $t1, g_h($zero)
	subu $t0, $t0, $t1
	lw $t1, g_i($zero)
	addu $t0, $t0, $t1
	sw $t0, g_e($zero)
	lw $t0, g_j($zero)
	lw $t1, g_k($zero)
	mul $t0, $t0, $t1
	lw $t1, g_l($zero)
	mul $t0, $t0, $t1
	lw $t1, g_m($zero)
	lw $t2, g_n($zero)
	div $t1, $t1, $t2
	subu $t0, $t0, $t1
	lw $t1, g_o($zero)
	addu $t0, $t0, $t1
	sw $t0, g_j($zero)
	lw $t0, g_p($zero)
	lw $t1, g_q($zero)
	addu $t0, $t0, $t1
	lw $t1, g_r($zero)
	lw $t2, g_s($zero)
	addu $t1, $t1, $t2
	mul $t0, $t0, $t1
	lw $t1, g_t($zero)
	div $t0, $t0, $t1
	lw $t1, g_u($zero)
	subu $t0, $t0, $t1
	sw $t0, g_p($zero)
	lw $t0, g_v($zero)
	lw $t1, g_w($zero)
	subu $t0, $t0, $t1
	lw $t1, g_xx2($zero)
	lw $t2, g_y2($zero)
	mul $t1, $t1, $t2
	addu $t0, $t0, $t1
	lw $t1, g_z2($zero)
	subu $t0, $t0, $t1
	lw $t1, g_aa2($zero)
	addu $t0, $t0, $t1
	sw $t0, g_v($zero)
	lw $t0, g_b2($zero)
	lw $t1, g_c2($zero)
	mul $t0, $t0, $t1
	lw $t1, g_d2($zero)
	subu $t0, $t0, $t1
	lw $t1, g_e2($zero)
	lw $t2, g_ff2($zero)
	mul $t1, $t1, $t2
	addu $t0, $t0, $t1
	lw $t1, g_g2($zero)
	subu $t0, $t0, $t1
	sw $t0, g_b2($zero)
	lw $t0, g_h2($zero)
	lw $t1, g_i2($zero)
	lw $t2, g_j2($zero)
	mul $t1, $t1, $t2
	addu $t0, $t0, $t1
	lw $t1, g_k2($zero)
	subu $t0, $t0, $t1
	lw $t1, g_l($zero)
	lw $t2, g_m($zero)
	mul $t1, $t1, $t2
	addu $t0, $t0, $t1
	sw $t0, g_h2($zero)
	lw $t0, -8($sp)
	lw $t1, -12($sp)
	addu $t0, $t0, $t1
	lw $t1, -16($sp)
	lw $t2, -20($sp)
	addu $t1, $t1, $t2
	mul $t0, $t0, $t1
	lw $t1, -24($sp)
	lw $t2, -28($sp)
	addu $t1, $t1, $t2
	lw $t2, -32($sp)
	div $t1, $t1, $t2
	subu $t0, $t0, $t1
	sw $t0, -8($sp)
	lw $t0, -36($sp)
	lw $t1, -40($sp)
	mul $t0, $t0, $t1
	lw $t1, -44($sp)
	addu $t0, $t0, $t1
	lw $t1, -48($sp)
	subu $t0, $t0, $t1
	lw $t1, -52($sp)
	addu $t0, $t0, $t1
	sw $t0, -36($sp)
	lw $t0, -56($sp)
	lw $t1, -60($sp)
	mul $t0, $t0, $t1
	lw $t1, -64($sp)
	mul $t0, $t0, $t1
	lw $t1, -68($sp)
	lw $t2, -72($sp)
	div $t1, $t1, $t2
	subu $t0, $t0, $t1
	lw $t1, -76($sp)
	addu $t0, $t0, $t1
	sw $t0, -56($sp)
	lw $t0, -80($sp)
	lw $t1, -84($sp)
	addu $t0, $t0, $t1
	lw $t1, -88($sp)
	lw $t2, -92($sp)
	addu $t1, $t1, $t2
	mul $t0, $t0, $t1
	lw $t1, -96($sp)
	div $t0, $t0, $t1
	lw $t1, -100($sp)
	subu $t0, $t0, $t1
	sw $t0, -80($sp)
	lw $t0, -104($sp)
	lw $t1, -108($sp)
	subu $t0, $t0, $t1
	lw $t1, -112($sp)
	lw $t2, -116($sp)
	mul $t1, $t1, $t2
	addu $t0, $t0, $t1
	lw $t1, -120($sp)
	subu $t0, $t0, $t1
	lw $t1, -124($sp)
	addu $t0, $t0, $t1
	sw $t0, -104($sp)
	lw $t0, -128($sp)
	lw $t1, -132($sp)
	mul $t0, $t0, $t1
	lw $t1, -136($sp)
	subu $t0, $t0, $t1
	lw $t1, -140($sp)
	lw $t2, -144($sp)
	mul $t1, $t1, $t2
	addu $t0, $t0, $t1
	lw $t1, -148($sp)
	subu $t0, $t0, $t1
	sw $t0, -128($sp)
	lw $t0, -152($sp)
	lw $t1, -156($sp)
	lw $t2, -160($sp)
	mul $t1, $t1, $t2
	addu $t0, $t0, $t1
	lw $t1, -164($sp)
	subu $t0, $t0, $t1
	lw $t1, -64($sp)
	lw $t2, -68($sp)
	mul $t1, $t1, $t2
	addu $t0, $t0, $t1
	sw $t0, -152($sp)
	lw $t0, g_x($zero)
	lw $t1, g_y($zero)
	addu $t0, $t0, $t1
	lw $t1, g_z($zero)
	addu $t0, $t0, $t1
	lw $t1, g_a($zero)
	addu $t0, $t0, $t1
	lw $t1, g_b($zero)
	addu $t0, $t0, $t1
	lw $t1, g_c($zero)
	addu $t0, $t0, $t1
	lw $t1, g_d($zero)
	addu $t0, $t0, $t1
	lw $t1, g_e($zero)
	addu $t0, $t0, $t1
	lw $t1, g_f($zero)
	addu $t0, $t0, $t1
	lw $t1, g_g($zero)
	addu $t0, $t0, $t1
	lw $t1, g_h($zero)
	addu $t0, $t0, $t1
	lw $t1, g_i($zero)
	addu $t0, $t0, $t1
	lw $t1, g_j($zero)
	addu $t0, $t0, $t1
	lw $t1, g_k($zero)
	addu $t0, $t0, $t1
	lw $t1, g_l($zero)
	addu $t0, $t0, $t1
	lw $t1, g_m($zero)
	addu $t0, $t0, $t1
	lw $t1, g_n($zero)
	addu $t0, $t0, $t1
	lw $t1, g_o($zero)
	addu $t0, $t0, $t1
	lw $t1, g_p($zero)
	addu $t0, $t0, $t1
	lw $t1, g_q($zero)
	addu $t0, $t0, $t1
	lw $t1, g_r($zero)
	addu $t0, $t0, $t1
	lw $t1, g_s($zero)
	addu $t0, $t0, $t1
	lw $t1, g_t($zero)
	addu $t0, $t0, $t1
	lw $t1, g_u($zero)
	addu $t0, $t0, $t1
	lw $t1, g_v($zero)
	addu $t0, $t0, $t1
	lw $t1, g_w($zero)
	addu $t0, $t0, $t1
	lw $t1, g_xx2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_y2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_z2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_aa2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_b2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_c2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_d2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_e2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_ff2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_g2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_h2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_i2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_j2($zero)
	addu $t0, $t0, $t1
	lw $t1, g_k2($zero)
	addu $t0, $t0, $t1
	lw $t1, -8($sp)
	addu $t0, $t0, $t1
	lw $t1, -12($sp)
	addu $t0, $t0, $t1
	lw $t1, -16($sp)
	addu $t0, $t0, $t1
	lw $t1, -20($sp)
	addu $t0, $t0, $t1
	lw $t1, -24($sp)
	addu $t0, $t0, $t1
	lw $t1, -28($sp)
	addu $t0, $t0, $t1
	lw $t1, -32($sp)
	addu $t0, $t0, $t1
	lw $t1, -36($sp)
	addu $t0, $t0, $t1
	lw $t1, -40($sp)
	addu $t0, $t0, $t1
	lw $t1, -44($sp)
	addu $t0, $t0, $t1
	lw $t1, -48($sp)
	addu $t0, $t0, $t1
	lw $t1, -52($sp)
	addu $t0, $t0, $t1
	lw $t1, -56($sp)
	addu $t0, $t0, $t1
	lw $t1, -60($sp)
	addu $t0, $t0, $t1
	lw $t1, -64($sp)
	addu $t0, $t0, $t1
	lw $t1, -68($sp)
	addu $t0, $t0, $t1
	lw $t1, -72($sp)
	addu $t0, $t0, $t1
	lw $t1, -76($sp)
	addu $t0, $t0, $t1
	lw $t1, -80($sp)
	addu $t0, $t0, $t1
	lw $t1, -84($sp)
	addu $t0, $t0, $t1
	lw $t1, -88($sp)
	addu $t0, $t0, $t1
	lw $t1, -92($sp)
	addu $t0, $t0, $t1
	lw $t1, -96($sp)
	addu $t0, $t0, $t1
	lw $t1, -100($sp)
	addu $t0, $t0, $t1
	lw $t1, -104($sp)
	addu $t0, $t0, $t1
	lw $t1, -108($sp)
	addu $t0, $t0, $t1
	lw $t1, -112($sp)
	addu $t0, $t0, $t1
	lw $t1, -116($sp)
	addu $t0, $t0, $t1
	lw $t1, -120($sp)
	addu $t0, $t0, $t1
	lw $t1, -124($sp)
	addu $t0, $t0, $t1
	lw $t1, -128($sp)
	addu $t0, $t0, $t1
	lw $t1, -132($sp)
	addu $t0, $t0, $t1
	lw $t1, -136($sp)
	addu $t0, $t0, $t1
	lw $t1, -140($sp)
	addu $t0, $t0, $t1
	lw $t1, -144($sp)
	addu $t0, $t0, $t1
	lw $t1, -148($sp)
	addu $t0, $t0, $t1
	lw $t1, -152($sp)
	addu $t0, $t0, $t1
	lw $t1, -156($sp)
	addu $t0, $t0, $t1
	lw $t1, -160($sp)
	addu $t0, $t0, $t1
	lw $t1, -164($sp)
	addu $t0, $t0, $t1
	sw $t0, -168($sp)
	lw $t0, -168($sp)
	li $k0, 1431655766
	mult $k0, $t0
	mfhi $k0
	sra $k0, $k0, 0
	sra $k1, $t0, 31
	subu $t0, $k0, $k1
	lw $t1, -168($sp)
	addu $t0, $t0, $t1
	sll $t0, $t0, 3
	lw $t1, -152($sp)
	addu $t0, $t0, $t1
	addiu $t0, $t0, 15
	sw $t0, -172($sp)
	lw $t0, g_x($zero)
	lw $t1, g_y($zero)
	addu $t0, $t0, $t1
	lw $t1, g_z($zero)
	addu $t0, $t0, $t1
	sw $t0, -64($sp)
	lw $t0, g_a($zero)
	lw $t1, g_b($zero)
	mul $t0, $t0, $t1
	lw $t1, g_c($zero)
	subu $t0, $t0, $t1
	sw $t0, -68($sp)
	lw $t0, g_d($zero)
	lw $t1, g_e($zero)
	div $t0, $t0, $t1
	lw $t1, g_f($zero)
	addu $t0, $t0, $t1
	sw $t0, -72($sp)
	lw $t0, g_g($zero)
	lw $t1, g_h($zero)
	addu $t0, $t0, $t1
	lw $t1, g_i($zero)
	lw $t2, g_j($zero)
	subu $t1, $t1, $t2
	mul $t0, $t0, $t1
	sw $t0, -76($sp)
	lw $t0, g_k($zero)
	lw $t1, g_l($zero)
	mul $t0, $t0, $t1
	lw $t1, g_m($zero)
	addu $t0, $t0, $t1
	sw $t0, -80($sp)
	lw $t0, -64($sp)
	lw $t1, -68($sp)
	subu $t0, $t0, $t1
	lw $t1, -72($sp)
	addu $t0, $t0, $t1
	sw $t0, -64($sp)
	lw $t0, -76($sp)
	lw $t1, -80($sp)
	mul $t0, $t0, $t1
	sw $t0, -76($sp)
	lw $t0, -64($sp)
	lw $t1, -76($sp)
	div $t0, $t0, $t1
	sw $t0, -80($sp)
	lw $t0, -88($sp)
	lw $t1, -92($sp)
	addu $t0, $t0, $t1
	lw $t1, -96($sp)
	subu $t0, $t0, $t1
	sw $t0, -84($sp)
	lw $t0, -104($sp)
	lw $t1, -108($sp)
	mul $t0, $t0, $t1
	lw $t1, -112($sp)
	addu $t0, $t0, $t1
	sw $t0, -100($sp)
	lw $t0, -124($sp)
	lw $t1, -128($sp)
	addu $t0, $t0, $t1
	lw $t1, -132($sp)
	lw $t2, -136($sp)
	subu $t1, $t1, $t2
	mul $t0, $t0, $t1
	sw $t0, -116($sp)
	lw $t0, -140($sp)
	lw $t1, -144($sp)
	addu $t0, $t0, $t1
	lw $t1, -148($sp)
	subu $t0, $t0, $t1
	sw $t0, -120($sp)
	lw $t0, -64($sp)
	lw $t1, -68($sp)
	addu $t0, $t0, $t1
	lw $t1, -72($sp)
	addu $t0, $t0, $t1
	lw $t1, -76($sp)
	addu $t0, $t0, $t1
	lw $t1, -80($sp)
	addu $t0, $t0, $t1
	lw $t1, -84($sp)
	addu $t0, $t0, $t1
	lw $t1, -100($sp)
	addu $t0, $t0, $t1
	lw $t1, -116($sp)
	addu $t0, $t0, $t1
	lw $t1, -120($sp)
	addu $t0, $t0, $t1
	sw $t0, -176($sp)
	la $t8, g_dqr0($zero)
	addu $t0, $t8, $zero
	la $a0, g_dqr0($zero)
	li $v0, 4
	syscall
	lw $t1, -168($sp)
	addu $a0, $t1, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr1($zero)
	addu $t1, $t8, $zero
	la $a0, g_dqr1($zero)
	li $v0, 4
	syscall
	lw $t2, -172($sp)
	addu $a0, $t2, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr2($zero)
	addu $t2, $t8, $zero
	la $a0, g_dqr2($zero)
	li $v0, 4
	syscall
	lw $t3, -176($sp)
	addu $a0, $t3, $zero
	li $v0, 1
	syscall
	la $t8, g_dqr3($zero)
	addu $t3, $t8, $zero
	la $a0, g_dqr3($zero)
	li $v0, 4
	syscall
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
func_main_block_449:
