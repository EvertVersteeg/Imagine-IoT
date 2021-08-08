					.global inv_pint
					.text
inv_pint:
					cmp	r1,	#0
					ble	exit
next:
					ldr	r2,	[r0]
					neg	r2,r2
					str	r2,	[r0]
					sub	r1,	r1,	#1
					beq	exit
					add	r0,	r0,	#4
					b	next
exit:
					bx	lr
