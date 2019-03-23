.name "sti_ldi_lldi"
.comment "I will bug you up"

# toujours valeur en 32 stocke dans un registre

l2:		sti r1, %:live, %1
		sti	r2, %:live, %1
		sti	r3, %:live, %1
		sti	r4, %:live, %1
		sti	r5, %:live, %1
		sti	r6, %:live, %1
		sti	r7, %:live, %1
		sti	r8, %:live, %9
		sti	r9, %:live, %17
		sti	r10, %:live, %1
		sti	r11, %:live, %2
		sti	r12, %:live, %1
		sti	r13, 25, r9
		sti	r14, 2, %1
		sti r15, 1, %2
		sti r16, %:live, %2
		aff r1
		and r1, %0, r1

live:	live %1
		zjmp %:live
