v0 = 0
v1 = 0
f_main [0] [0]
a1 = 0
loadaddr v1 a0
a0[0] = a1
a1 = 3
loadaddr v0 a0
a0[0] = a1
l1 :
a1 = 0
loadaddr v0 a0
a0 = a0[0]
a1 = a0 > a1
a0 = 0
if a1 == a0 goto l0
loadaddr v1 a0
a1 = a0[0]
loadaddr v0 a0
a0 = a0[0]
a1 = a1 + a0
loadaddr v1 a0
a0[0] = a1
a1 = 1
loadaddr v0 a0
a0 = a0[0]
a1 = a0 - a1
loadaddr v0 a0
a0[0] = a1
goto l1
l0 :
loadaddr v1 a0
a0 = a0[0]
return
return
end f_main
v2 = 0
