v0 = 0
v1 = malloc 40
f_main [0] [5]
store a1 0
store a2 1
store a3 2
store a4 3
store a5 4
call f_getint
load 0 a1
load 1 a2
load 2 a3
load 3 a4
load 4 a5
a1 = a0
loadaddr v0 a2
a2[0] = a1
a2 = 10
loadaddr v0 a1
a1 = a1[0]
a2 = a1 > a2
a1 = 0
if a2 == a1 goto l0
a0 = 1
return
goto l1
l0 :
l1 :
a2 = 0
a1 = a2
l3 :
loadaddr v0 a3
a3 = a3[0]
a4 = a2 < a3
a3 = 0
if a4 == a3 goto l2
store a1 0
store a2 1
store a3 2
store a4 3
store a5 4
call f_getint
load 0 a1
load 1 a2
load 2 a3
load 3 a4
load 4 a5
a3 = a0
a5 = 4
a5 = a5 * a2
loadaddr v1 a4
a5 = a5 + a4
a5[0] = a3
a4 = 4
a4 = a4 * a2
loadaddr v1 a3
a4 = a4 + a3
a3 = a4[0]
a1 = a1 + a3
a3 = 1
a2 = a2 + a3
goto l3
l2 :
a0 = a1
store a1 0
store a2 1
store a3 2
store a4 3
store a5 4
call f_putint
load 0 a1
load 1 a2
load 2 a3
load 3 a4
load 4 a5
loadaddr v0 a2
a2[0] = a0
a0 = 10
store a1 0
store a2 1
store a3 2
store a4 3
store a5 4
call f_putchar
load 0 a1
load 1 a2
load 2 a3
load 3 a4
load 4 a5
loadaddr v0 a2
a2[0] = a0
a0 = a1
return
return
end f_main
v2 = 0
