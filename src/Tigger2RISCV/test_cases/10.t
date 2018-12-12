v0 = 0
f_main [0] [0]
a1 = 10
loadaddr v0 a0
a0[0] = a1
a1 = 0
loadaddr v0 a0
a0 = a0[0]
a1 = a0 > a1
a0 = 0
if a1 == a0 goto l0
a0 = 1
return
goto l1
l0 :
l1 :
a0 = 0
return
return
end f_main
v1 = 0
