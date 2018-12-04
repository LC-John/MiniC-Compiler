v0 = malloc 16
v1 = 0

f_main [0] [0]

loadaddr v0 t0
t1 = 100
t2 = t0 + 4
t2[0] = t1

loadaddr v0 t0
t2 = t0 + 4
a0 = t0[4]

return 

end f_main
