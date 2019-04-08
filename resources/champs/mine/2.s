.name 		"zork"
.comment 			"just a basic living prog"

#.name "dasjhdkasjdhksajhd"

l2:sti	r1,%:live,%1
	and	r1,%0,r1
	ldi %:live,%1,r16
	sti r16, %:live, %100

live:	live	%1
	zjmp	%:live
