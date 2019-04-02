.name "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"
.comment "just testing"

live %4294967295

ld %19283, r8
ld -19289, r7

st r6, r7
st r1, 65535

add r8, r7, r15

sub r12,r11,r10

and r12,r10,r11
and %10,r14,r15
and r12,%-10,r15
and %199,%90,r15

or r12,r10,r11
or %10,r14,r15
or r12,%-10,r15
or %199,%90,r15

xor r12,r10,r11
xor %-10,r14,r15
xor r12,%-10,r15
xor %199,%-90,r15

zjmp %4294967295

ldi %-9873465, r3, r1
ldi r2, %654, r3
ldi %5, %9, r4
ldi 5, %10, r5
ldi 5, r13, r5

sti r1, %-173, r3
sti r1, 173, r4
sti r1, r2, %1005

fork %42

lld %50, r16
lld 50, r16

lldi %-9873465, r3, r1
lldi r2, %654, r3
lldi %5, %9, r4
lldi 5, %10, r5
lldi 5, r13, r5

lfork %4242

aff r8
