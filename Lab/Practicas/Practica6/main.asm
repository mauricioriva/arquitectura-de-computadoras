.data
arr:	.word 1 2 3 4 5 6 7 8 9 10 11 
arr2:	.space 48
arrlen:	.word 11
arg1:	.word 1
arg2:	.word 2
arg3:	.word 3
arg4:	.word 4
arg5:	.word 5


.text

.globl main

main:	la	$a0 arr
	lw	$a1 arrlen
	jal	sort
	li	$v0 10
	syscall
	
