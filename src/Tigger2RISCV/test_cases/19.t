v0 = 0
v1 = 0
v2 = 0
f_main [0] [2]
store a1 0
store a2 1
call f_getint
load 0 a1
load 1 a2
a1 = a0
loadaddr v0 a2
a2[0] = a1
store a1 0
store a2 1
call f_getint
load 0 a1
load 1 a2
a1 = a0
loadaddr v1 a2
a2[0] = a1
store a1 0
store a2 1
call f_getint
load 0 a1
load 1 a2
loadaddr v2 a1
a1[0] = a0
loadaddr v1 a0
a1 = a0[0]
loadaddr v2 a0
a0 = a0[0]
a1 = a1 * a0
loadaddr v0 a0
a0 = a0[0]
a0 = a0 + a1
return
return
end f_main
v3 = 0
