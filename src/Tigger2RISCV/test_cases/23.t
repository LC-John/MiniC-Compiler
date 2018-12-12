v0 = 0
f_f [1] [2]
a1 = 1
a2 = a0 == a1
a1 = 0
if a2 == a1 goto l0
a0 = 1
return
goto l1
l0 :
l1 :
a1 = 2
a2 = a0 == a1
a1 = 0
if a2 == a1 goto l2
a0 = 1
return
goto l3
l2 :
l3 :
a1 = 1
a2 = a0 - a1
a1 = 2
a1 = a0 - a1
a0 = a2
store a1 0
store a2 1
call f_f
load 0 a1
load 1 a2
a2 = a0
a0 = a1
store a1 0
store a2 1
call f_f
load 0 a1
load 1 a2
a0 = a2 + a0
return
return
end f_f
v1 = 0
f_main [0] [2]
store a1 0
store a2 1
call f_getint
load 0 a1
load 1 a2
loadaddr v0 a1
a1[0] = a0
loadaddr v0 a0
a0 = a0[0]
store a1 0
store a2 1
call f_f
load 0 a1
load 1 a2
a1 = a0
a0 = a1
store a1 0
store a2 1
call f_putint
load 0 a1
load 1 a2
loadaddr v0 a2
a2[0] = a0
a0 = 10
store a1 0
store a2 1
call f_putchar
load 0 a1
load 1 a2
loadaddr v0 a2
a2[0] = a0
a0 = a1
return
return
end f_main
v2 = 0
