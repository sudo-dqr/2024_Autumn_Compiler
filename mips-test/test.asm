.text
li $t0, 1
sw $t0, 0($sp)
addi $sp, $sp, -4
li $t1, 2
sw $t1, 0($sp)
lw $k0, 0($sp)
addi $sp, $sp, 4
lw $k1, 0($sp)
add $t0, $k0, $k1
move $a0, $t0
li $v0, 1
syscall

