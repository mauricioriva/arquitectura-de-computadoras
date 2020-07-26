.data
msg:	.asciiz "Ingresa un número entero: "

#Termina la ejecucion del programa  con una llamada al sistema.
.macro end()
	li 	$v0, 10       	
	syscall				# Llamada al sistema.
.end_macro


#Lee un entero de la terminal y lo guarda en %rd.
.macro read_int(%rd)
	li 	$v0, 4			
	la 	$a0, msg		
	syscall				

	li 	$v0, 5			
	syscall				# Llamada al sistema.
	move 	%rd, $v0	
.end_macro

#Imprime en la terminal el entero guardado  en %rs.
.macro print_int(%rs)
	move 	$a0, %rs	
	li 	$v0, 1			
	syscall				# Llamada al sistema.
.end_macro

#Preambulo de foo como rutina invocada.
.macro pre_foo0()
	addi 	$sp, $sp, -12
	sw 	$a0, 4($sp)		
	sw 	$ra, 0($sp)		
.end_macro

#Conclusion de foo como rutina invodada.
.macro con_foo0()
	lw 	$ra, 0($sp)		
	addi 	$sp, $sp, 12
	jr 	$ra			
.end_macro

#Preambulo para invocar foo(n-1).
.macro pre_foo1()	
	addi 	$a0, $a0, -1		# n = n - 1
.end_macro

# Conclusion de la invocacion de foo(n-1).
.macro con_foo1()
	lw 	$a0, 4($sp)		
	sw	$v0, 8($sp)		# Resultado de foo(n-1).
.end_macro

# Preambulo para invocar foo(n-2).
.macro pre_foo2()
	addi 	$a0, $a0, -2		# n = n - 2.
.end_macro


# Conclusion de la invocacion de foo(n-2).
.macro con_foo2()
	lw 	$t0, 8($sp)		
.end_macro

# Invocacion a la subrutina foo.
.macro inv_foo()
	jal foo 			
.end_macro


.text
	read_int($a0)		# Lee un entero 'n'.
	
	inv_foo()			
	
	print_int($v0)			
	end()				# Termina.


foo:	
	pre_foo0()			
	beq	$a0, 1, base1	
	beq 	$a0, 2, base1
	pre_foo1()			
	inv_foo()			
	con_foo1()			
	move 	$t0, $v0	
	pre_foo2()			
	inv_foo()			
	con_foo2()			
	add 	$v0, $v0, $t0		
	j return		

base1:	li 	$v0, 1		
return: con_foo0()	
