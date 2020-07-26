.data
array:	.word	10,8,6,7,9,4,5,2,1,3
n:	.word	10

.text
	la $a0 array 
	lw $a1 n 
	jal ordena  
	move $t0 $v0 
	li $v0 10 #Termina
	syscall

ordena:	subi $sp $sp 32 
	sw $ra 16($sp) 
	sw $fp 20($sp) 
	addi $fp $sp 28 
	move $t1 $a0 
ciclo:	mul $t0 $a1 4 
	add $t0 $t0 $a0 
	bge $t1 $t0 cambia 
	move $t2 $t1 
	add $t3 $t1 4 
ciclo1:	bge $t3 $t0 if2 
	lw $t4 ($t2) 
	lw $t5 ($t3) 
	bge $t5 $t4 if 
	move $t2 $t3
if:	add $t3 $t3 4 
	j ciclo1
if2:	
	sw $a0 0($sp) 
	sw $a1 4($sp) 
	sw $t1 28($sp) 
	move $a0 $t1 
	move $a1 $t2 
	jal intercambia 
	lw $a0 0($sp) 
	lw $a1 4($sp) 
	lw $t1 28($sp) 
	add $t1 $t1 4 
	j ciclo

cambia:	move $v0 $zero 
	lw $ra 16($sp) 
	lw $fp 20($sp) 
	addi $sp $sp 32 
	jr $ra 

intercambia:	subi $sp $sp 8 
	sw $ra ($sp) 
	sw $fp 4($sp) 
	addi $fp $sp 4 
	lw $t0 ($a0) 
	lw $t1 ($a1) 
	sw $t0 ($a1) 
	sw $t1 ($a0) 
	lw $ra ($sp) 
	lw $fp 4($sp) 
	addi $sp $sp 8 
	jr $ra 
