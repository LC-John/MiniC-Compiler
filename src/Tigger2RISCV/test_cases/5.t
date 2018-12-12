v0 = 0
f_func [1] [0]
a1 = 1
a0 = a0 - a1
return
return
end f_func
v1 = 0
f_main [0] [1]
a1 = 10
loadaddr v0 a0
a0[0] = a1
loadaddr v0 a0
a0 = a0[0]
store a1 0
call f_func
load 0 a1
return
return
end f_main
v2 = 0
