.data
x:	.word 2
n:	.word 10

.text
	lw	$a0 x
	lw	$a1 n #paso1 poner argumentos
	nop	      #paso2 guardar registros
	jal	powr
	move	$a0 $v0
	li	$v0 1
	syscall
	li	$v0 10
	syscall
	
powr:	subi	$sp $sp 32 	# paso1: reservar espacio(no hay paso2)
	sw	$ra 16($sp)	# paso3: guardar direccion de retorno
	sw	$fp 20($sp)	# paso4: guardar fp
	addi	$fp $sp 28 	# paso4: establecer apuntador al marco
	beqz	$a1 ret1	#caso base0
	beq	$a1 1 retx	#caso base1
	rem	$t0 $a1 2	# n%2
	beqz	$t0 esPar
	sw	$a1 24($sp)	#es impar, guardo n actual
	subi	$a1 $a1 1 	# n = n-1
	jal	powr		#powr(x,n-1)
	lw	$a1 24($sp)	#restaurar n
	mul	$v0 $v0 $a0	# x * pow(x,n-1)
	j	end
esPar:	sw	$a1 24($sp)	#es par, guardo n actual
	div	$a1 $a1 2	# n =n/2
	jal	powr		#powr(x,n/2)
	lw	$a1 24($sp)	#retaurar n
	mul	$v0 $v0 $v0     #powr(x,n/2)^2
	j	end
ret1:	li	$v0 1
	j	end
retx:	move	$v0 $a0		#paso1: retornar resultados
end:	lw	$ra 16($sp)    #paso2: restaurar valores
	lw	$fp 20($sp)	#paso2:
	addi	$sp $sp	32	#paso3: eliminar el marco
	jr	$ra		#paso4: regresar el control