v0 = 0
f_main [0] [12]
store s0 0
store s1 1
store s2 2
store s3 3
store s4 4
store s5 5
store s6 6
store s7 7
store s8 8
store s9 9
store s10 10
store s11 11
call f_getint
s2 = a0
l1 :
s0 = 5
s1 = s2 == s0
s0 = 0
if s1 == s0 goto l0
s0 = 1
s2 = s2 + s0
goto l1
l0 :
a0 = 0
s0 = 1
t6 = a0 + s0
s0 = 1
t5 = t6 + s0
s0 = 1
t4 = t5 + s0
s0 = 1
t3 = t4 + s0
s0 = 1
t2 = t3 + s0
s0 = 1
t1 = t2 + s0
s0 = 1
t0 = t1 + s0
s0 = 1
a7 = t0 + s0
s0 = 1
a6 = a7 + s0
s0 = 1
a5 = a6 + s0
s0 = 1
a4 = a5 + s0
s0 = 1
a3 = a4 + s0
s0 = 1
a2 = a3 + s0
s0 = 1
a1 = a2 + s0
s0 = 1
s11 = a1 + s0
s0 = 1
s10 = s11 + s0
s0 = 1
s9 = s10 + s0
s0 = 1
s8 = s9 + s0
s0 = 1
s7 = s8 + s0
s0 = 1
s6 = s7 + s0
s0 = 1
s5 = s6 + s0
s0 = 1
s4 = s5 + s0
s0 = 1
s3 = s4 + s0
s0 = 1
s1 = s3 + s0
s0 = 1
s0 = s1 + s0
call f_putint
a0 = t6
call f_putint
a0 = t5
call f_putint
a0 = t4
call f_putint
a0 = t3
call f_putint
a0 = t2
call f_putint
a0 = t1
call f_putint
a0 = t0
call f_putint
a0 = a7
call f_putint
a0 = a6
call f_putint
a0 = a5
call f_putint
a0 = a4
call f_putint
a0 = a3
call f_putint
a0 = a2
call f_putint
a0 = a1
call f_putint
a0 = s11
call f_putint
a0 = s10
call f_putint
a0 = s9
call f_putint
a0 = s8
call f_putint
a0 = s7
call f_putint
a0 = s6
call f_putint
a0 = s5
call f_putint
a0 = s4
call f_putint
a0 = s3
call f_putint
a0 = s1
call f_putint
a0 = s0
call f_putint
s1 = 10
a0 = s1
call f_putchar
a0 = s2
call f_putint
a0 = s1
call f_putchar
a0 = s0
load 0 s0
load 1 s1
load 2 s2
load 3 s3
load 4 s4
load 5 s5
load 6 s6
load 7 s7
load 8 s8
load 9 s9
load 10 s10
load 11 s11
return
load 0 s0
load 1 s1
load 2 s2
load 3 s3
load 4 s4
load 5 s5
load 6 s6
load 7 s7
load 8 s8
load 9 s9
load 10 s10
load 11 s11
return
end f_main
