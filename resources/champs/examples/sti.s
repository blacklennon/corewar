.name "sti_ldi_lldi"
.comment "I will bug you up"

# toujours valeur en 32 stocke dans un registre

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
