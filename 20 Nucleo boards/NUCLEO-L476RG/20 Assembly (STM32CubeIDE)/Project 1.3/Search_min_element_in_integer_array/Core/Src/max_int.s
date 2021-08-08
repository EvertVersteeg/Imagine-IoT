				.global max_int
				.text
max_int:
				ldr	r2,	[r0]
next:
				ldr	r3,	[r0, #4]
				cmp	r2,	r3
				bgt	cont
				mov	r2,	r3
cont:
				add	r0,	r0,	#4
				sub	r1,	r1,	#1
				cmp r1, #1
				beq exit
				b	next
exit:
				mov	r0, r2
				bx	lr
