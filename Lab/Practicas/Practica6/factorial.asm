.data
n: .word 5


.text
	lw $a0 n #pasar argumentos
	jal fact  #llamada a la subrutina
	move $t0 $v0 
	li $v0 10 #codigo para terminar ejecucion
	syscall

fact:	subi $sp $sp 32 #reservamos espacio en la pila push
	sw $ra 16($sp) #respaldamos la direccion de retorno
	sw $fp 20($sp) # respaldamo el fp
	addi $fp $sp 28 # establecemos el nuevo fp
	beqz $a0 r1    
	sw $a0 28($sp) # respaldamos n
	subi $a0 $a0 1 #actializamos n para hacer la llamada fact(n-1)
	jal fact # invocacion a fib
	lw $a0 28($sp) # restauramos n
	mul $v0 $a0 $v0 # calculamos n * fact(n-1) y lo preparamos como valor de retorno
	j con #saldo a la conclusion de la subrutina
r1:	li $v0 1 # preparamos un 1 para regresarlo como valor de retorno(saltamos aqui en el caso base)
con:	lw $ra 16($sp) #comienza la conclusion de la subrutina. Restauramos la direccion de retorno
	lw $fp 20($sp) #restauramos el fp
	addi $sp $sp 32 # regresamos el sp para liberar la memoria pop (la memoria no se borra)
	jr $ra #regresamos el control al invocador
	
	
