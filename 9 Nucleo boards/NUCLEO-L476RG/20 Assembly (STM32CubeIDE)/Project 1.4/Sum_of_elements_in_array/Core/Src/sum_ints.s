				.global	sum_ints
				.text
sum_ints:
				mov	r2, #0
next:			ldr	r3, [r0]
				add	r2,	r2,	r3
				sub	r1,	r1,	#1
				cmp	r1,	#0
				beq	exit
				add	r0,	r0,	#4
				b	next
exit:
				mov	r0,	r2
				bx	lr