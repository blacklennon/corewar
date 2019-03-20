.name		"fork"
.comment	"Tests fork"

sti			r1, %:live, %1
and			r1, %0, r1

fork		%:live

live:
live		%1
zjmp		%:live
