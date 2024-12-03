.data


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
	lw $t8, -8($sp)
	sw $t8, -20($sp)
	lw $t8, -12($sp)
	sw $t8, -24($sp)
	lw $t8, 0($sp)
	sw $t8, -16($sp)
	li $v0, 0
	lw $ra, -4($sp)
	jr $ra
