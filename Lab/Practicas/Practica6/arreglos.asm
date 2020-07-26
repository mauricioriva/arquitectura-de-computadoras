.data
arr:	.word	2 3 5 6 8 9 5 3 5
larr:	.word	9

.text
	la	$t0 arr #arr
	lw	$t1 ($t0)
	lw	$t2 larr #larr
	li	$s0 0 # total = 0
	li	$s1 0 #	i = 0
while:	blt	$s1 $t2 cw#while(i<larr)
	j	endw
cw:	add	$s0 $s0 $t1 # total = total + arr[i]
	addi	$s1 $s1 1 # i = i +1
	addi	$t0 $t0 4
	lw	$t1 ($t0)
	j	while
endw:	