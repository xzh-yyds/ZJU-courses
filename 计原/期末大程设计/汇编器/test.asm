add $t0 $t3 $zero;
label:addi $t0 $t0 1;
lw $t0 8($s6);
sw $t0 -3($s5);
beq $t0 $t1 label;
j label;