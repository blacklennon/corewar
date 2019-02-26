.name 		"zork"
.comment 			"just a basic living prog"

#.name "dasjhdkasjdhksajhd"

l2:sti	r1,%:live,%1
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live


#
# label "l2"
# op "sti"
# register 1
# separator
# direct ":live"
# separator
# direct 1
# eoi
# label "live"
# op "live"
# direct 1
# op "zjump"
# direct ":live"
