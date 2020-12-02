global out_8

out_8:
	mov	edx, [esp+4]
	mov	eax, [esp+8]

	out	dx, al

	ret
