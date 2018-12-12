v0 = 0
f_fib [1] [0]
a3 = 0
a2 = 1
a4 = 0
a5 = a0 == a4
a4 = 0
if a5 == a4 goto l0
a0 = 0
return
goto l1
l0 :
l1 :
a4 = 1
a5 = a0 == a4
a4 = 0
if a5 == a4 goto l2
a0 = 1
return
goto l3
l2 :
l3 :
l5 :
a4 = 1
a5 = a0 > a4
a4 = 0
if a5 == a4 goto l4
a1 = a3 + a2
a3 = a2
a2 = a1
a4 = 1
a0 = a0 - a4
goto l5
l4 :
a0 = a1
return
return
end f_fib
v1 = 0
f_main [0] [1]
store a1 0
call f_getint
load 0 a1
loadaddr v0 a1
a1[0] = a0
loadaddr v0 a0
a0 = a0[0]
store a1 0
call f_fib
load 0 a1
return
return
end f_main
v2 = 0
