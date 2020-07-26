.data
msg_n:	.asciiz "Ingresa un número: "
msg_k: 	.asciiz "Ingresa otro número: "

.macro end()
	li 	$v0, 10       	
	syscall				# Llamada al sistema.
.end_macro


.macro read_int(%rd, %msg)
	move	$t0, $a0		
	li 	$v0, 4			
	la 	$a0, %msg		
	syscall				
	move 	$a0, $t0		
	li 	$v0, 5			
	syscall				
	move 	%rd, $v0	
.end_macro


.macro print_int(%rs)
	move 	$a0, %rs	
	li 	$v0, 1			
	syscall				
.end_macro


.macro pre_cf_binomial_0()
	addi 	$sp, $sp, -16	
	sw	$a1, 8($sp)		
	sw 	$a0, 4($sp)		
	sw 	$ra, 0($sp)		
.end_macro


.macro con_cf_binomial_0()
	lw 	$ra, 0($sp)		
	addi 	$sp, $sp, 16	
	jr 	$ra			
.end_macro


.macro pre_cf_binomial_1()
	addi 	$a0, $a0, -1		# n = n - 1.
	addi 	$a1, $a1, -1		# k = k - 1.
.end_macro

.macro con_cf_binomial_1()
	lw 	$a1, 8($sp)	
	lw 	$a0, 4($sp)	
	sw	$v0, 12($sp)
.end_macro

.macro pre_cf_binomial_2()
	addi 	$a0, $a0, -1		# n = n - 1.
.end_macro

.macro con_cf_binomial_2()
	lw 	$t0, 12($sp)
.end_macro


.macro inv_cf_binomial()
	jal cf_binomial 
.end_macro


.macro valida_caso_base_1(%n, %k)
	sge 	$t0, %n, $zero			
	seq 	$t1, %k, $zero		
	add 	$t2, $t0, $t1		
	beq 	$t2, 2, base_1		
.end_macro


.macro valida_caso_base_2(%n, %k)
	seq 	$t0, %n, $zero		
	sgt 	$t1, %k, $zero
	add 	$t2, $t0, $t1		
	beq 	$t2, 2, base_2		
.end_macro


	.text
	.globl main


main:
	read_int($a0, msg_n)		# Lee un entero 'n'.
	read_int($a1, msg_k)		# Lee un entero 'k'.
	inv_cf_binomial()		
	print_int($v0)			
	end()				


cf_binomial:
	pre_cf_binomial_0()	
	valida_caso_base_1($a0, $a1)
	valida_caso_base_2($a0, $a1)	
	pre_cf_binomial_1()	
	inv_cf_binomial()	
	con_cf_binomial_1()	
	move 	$t0, $v0	
	pre_cf_binomial_2()	
	inv_cf_binomial()	
	con_cf_binomial_2()	
	add 	$v0, $v0, $t0	
	j 	return			


return:
	con_cf_binomial_0()	
	

base_1:	
	li 	$v0, 1			
	j 	return			
	

base_2:	
	li 	$v0, 0			
	j 	return			
