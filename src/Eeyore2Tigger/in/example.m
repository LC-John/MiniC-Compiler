v0 = 0
v1 = 0
f_main [ 0 ] 
t0 = 10
loadaddr v0 e0
e0[0] = t0
t1 = 20
loadaddr v1 e1
e1[0] = t1
loadaddr v0 e2
e3 = e2[0]
t2 = e3
loadaddr v1 e4
e5 = e4[0]
t3 = e5
t4 = t2 + t3
T2 = t4
t5 = T2
__a0 = t5
return
return
end f_main
