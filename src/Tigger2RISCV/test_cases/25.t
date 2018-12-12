v0 = 0
v1 = malloc 420
v2 = 0
v3 = 0
f_main [0] [5]
a2 = 32
loadaddr v2 a1
a1[0] = a2
a2 = 10
loadaddr v3 a1
a1[0] = a2
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
a1 = 0
l1 :
loadaddr v0 a2
a2 = a2[0]
a3 = a1 < a2
a2 = 0
if a3 == a2 goto l0
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
a2 = a0
a4 = 4
a4 = a4 * a1
loadaddr v1 a3
a4 = a4 + a3
a4[0] = a2
a2 = 1
a1 = a1 + a2
goto l1
l0 :
a1 = 1
loadaddr v0 a0
a0 = a0[0]
a1 = a0 - a1
l3 :
a0 = 0
a2 = a1 > a0
a0 = 0
if a2 == a0 goto l2
a2 = 0
l5 :
a3 = a2 < a1
a0 = 0
if a3 == a0 goto l4
a3 = 4
a3 = a3 * a2
loadaddr v1 a0
a3 = a3 + a0
a4 = a3[0]
a0 = 1
a0 = a2 + a0
a3 = 4
a3 = a3 * a0
loadaddr v1 a0
a3 = a3 + a0
a0 = a3[0]
a3 = a4 > a0
a0 = 0
if a3 == a0 goto l6
a3 = 4
a3 = a3 * a2
loadaddr v1 a0
a3 = a3 + a0
a0 = a3[0]
a3 = 1
a3 = a2 + a3
a4 = 4
a4 = a4 * a3
loadaddr v1 a3
a4 = a4 + a3
a5 = a4[0]
a4 = 4
a4 = a4 * a2
loadaddr v1 a3
a4 = a4 + a3
a4[0] = a5
a3 = 1
a3 = a2 + a3
a4 = 4
a4 = a4 * a3
loadaddr v1 a3
a4 = a4 + a3
a4[0] = a0
goto l7
l6 :
l7 :
a0 = 1
a2 = a2 + a0
goto l5
l4 :
a0 = 1
a1 = a1 - a0
goto l3
l2 :
a1 = 0
l9 :
loadaddr v0 a0
a0 = a0[0]
a2 = a1 < a0
a0 = 0
if a2 == a0 goto l8
a2 = 4
a2 = a2 * a1
loadaddr v1 a0
a2 = a2 + a0
a0 = a2[0]
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
loadaddr v3 a0
a0 = a0[0]
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
a0 = 1
a1 = a1 + a0
goto l9
l8 :
a0 = 0
return
return
end f_main
v4 = 0
