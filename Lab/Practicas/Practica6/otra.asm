.data

.text
.globl otra sort

otra:	li	$v0 1
	li	$a0 10
	syscall
	jr	$ra 

sort:	move	$t0 $a0 # arr
	move	$t1 $a1 #arrlen
	subi	$t2 $t1 1
	mul	$t2 $t2 4 # size(arr)
	add	$t2 $t0 $t2 #
	div	$t4 $t1 2
loop:	ble	$t1 $t4 end
	lw	$a0 ($t0)# a[3] := lw	$a0 12($t0)
	li	$v0 1
	syscall
	lw	$t3 ($t2)
	sw	$t3 ($t0) # sobreescribe el primero con el ultimo
	sw	$a0 ($t2) # sobreescribe el ultimo con el primero
	add	$t0 $t0 4
	subi	$t2 $t2 4
	subi	$t1 $t1 1
	j	loop
end:	jr	$ra