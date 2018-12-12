v0 = malloc 20
f_main [0] [3]
a2 = 0
store a1 0
store a2 1
store a3 2
call f_getint
load 0 a1
load 1 a2
load 2 a3
a1 = a0
a3 = 4
a3 = a3 * a2
loadaddr v0 a2
a3 = a3 + a2
a3[0] = a1
a2 = 1
store a1 0
store a2 1
store a3 2
call f_getint
load 0 a1
load 1 a2
load 2 a3
a1 = a0
a3 = 4
a3 = a3 * a2
loadaddr v0 a2
a3 = a3 + a2
a3[0] = a1
a2 = 2
store a1 0
store a2 1
store a3 2
call f_getint
load 0 a1
load 1 a2
load 2 a3
a1 = a0
a3 = 4
a3 = a3 * a2
loadaddr v0 a2
a3 = a3 + a2
a3[0] = a1
a2 = 3
store a1 0
store a2 1
store a3 2
call f_getint
load 0 a1
load 1 a2
load 2 a3
a1 = a0
a3 = 4
a3 = a3 * a2
loadaddr v0 a2
a3 = a3 + a2
a3[0] = a1
a1 = 4
store a1 0
store a2 1
store a3 2
call f_getint
load 0 a1
load 1 a2
load 2 a3
a2 = 4
a2 = a2 * a1
loadaddr v0 a1
a2 = a2 + a1
a2[0] = a0
a1 = 4
a0 = 0
l1 :
a2 = 1
a3 = a1 > a2
a2 = 0
if a3 == a2 goto l0
a3 = 4
a3 = a3 * a1
loadaddr v0 a2
a3 = a3 + a2
a2 = a3[0]
a0 = a0 + a2
a2 = 1
a1 = a1 - a2
goto l1
l0 :
return
return
end f_main
v1 = 0
