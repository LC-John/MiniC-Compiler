v0 = 0
v1 = 0
f_main [0] [2]
store s0 0
store s1 1
s1 = 10
loadaddr v0 s0
s0[0] = s1
s1 = 20
loadaddr v1 s0
s0[0] = s1
loadaddr v0 s0
s1 = s0[0]
loadaddr v1 s0
s0 = s0[0]
a0 = s1 + s0
load 0 s0
load 1 s1
return
load 0 s0
load 1 s1
return
end f_main
