# Parse Tree Example

## Original MiniC Source Code

```C
// example.c
1  int a;
2  int b;
3  
4  int main(){
5  	a = 10;
6  	b = 20;
7  	int c;
8  	c = a + b;
9  	return c;
10  }
```

## Parse Tree Produced

```
// parse tree of example.c
[*]Root(31) at L10, P (N) L (N) R (N) C = 2 I = -1
  child(s) 1 of (31)
    [*]VarDefn(2) at L1, P (31) L (N) R (5) C = 3 I = 0
      child(s) 1 of (2)
        [*]Type(int)(0) at L1, P (2) L (N) R (N) C = 0 I = 0
      child(s) 2 of (2)
        [*]Id(a)(1) at L1, P (2) L (N) R (N) C = 0 I = 1
      child(s) 3 of (2)
        NONE
    [*]VarDefn(5) at L2, P (31) L (2) R (N) C = 3 I = 0
      child(s) 1 of (5)
        [*]Type(int)(3) at L2, P (5) L (N) R (N) C = 0 I = 0
      child(s) 2 of (5)
        [*]Id(b)(4) at L2, P (5) L (N) R (N) C = 0 I = 1
      child(s) 3 of (5)
        NONE
  child(s) 2 of (31)
    [*]FuncDefn(30) at L10, P (31) L (N) R (N) C = 4 I = 1
      child(s) 1 of (30)
        [*]Type(int)(6) at L4, P (30) L (N) R (N) C = 0 I = 0
      child(s) 2 of (30)
        [*]Id(main)(29) at L4, P (30) L (N) R (N) C = 0 I = 1
      child(s) 3 of (30)
        NONE
      child(s) 4 of (30)
        [*]StmtVarAssn(10) at L5, P (30) L (N) R (14) C = 2 I = 3
          child(s) 1 of (10)
            [*]Id(a)(7) at L5, P (10) L (N) R (N) C = 0 I = 0
          child(s) 2 of (10)
            [*]ExprInt(9) at L5, P (10) L (N) R (N) C = 1 I = 1
              child(s) 1 of (9)
                [*]Int(10)(8) at L5, P (9) L (N) R (N) C = 0 I = 0
        [*]StmtVarAssn(14) at L6, P (30) L (10) R (18) C = 2 I = 3
          child(s) 1 of (14)
            [*]Id(b)(11) at L6, P (14) L (N) R (N) C = 0 I = 0
          child(s) 2 of (14)
            [*]ExprInt(13) at L6, P (14) L (N) R (N) C = 1 I = 1
              child(s) 1 of (13)
                [*]Int(20)(12) at L6, P (13) L (N) R (N) C = 0 I = 0
        [*]StmtVarDefn(18) at L7, P (30) L (14) R (25) C = 1 I = 3
          child(s) 1 of (18)
            [*]VarDefn(17) at L7, P (18) L (N) R (N) C = 3 I = 0
              child(s) 1 of (17)
                [*]Type(int)(15) at L7, P (17) L (N) R (N) C = 0 I = 0
              child(s) 2 of (17)
                [*]Id(c)(16) at L7, P (17) L (N) R (N) C = 0 I = 1
              child(s) 3 of (17)
                NONE
        [*]StmtVarAssn(25) at L8, P (30) L (18) R (28) C = 2 I = 3
          child(s) 1 of (25)
            [*]Id(c)(19) at L8, P (25) L (N) R (N) C = 0 I = 0
          child(s) 2 of (25)
            [*]ExprBiArith(+)(24) at L8, P (25) L (N) R (N) C = 2 I = 1
              child(s) 1 of (24)
                [*]ExprId(21) at L8, P (24) L (N) R (N) C = 1 I = 0
                  child(s) 1 of (21)
                    [*]Id(a)(20) at L8, P (21) L (N) R (N) C = 0 I = 0
              child(s) 2 of (24)
                [*]ExprId(23) at L8, P (24) L (N) R (N) C = 1 I = 1
                  child(s) 1 of (23)
                    [*]Id(b)(22) at L8, P (23) L (N) R (N) C = 0 I = 0
        [*]StmtReturn(28) at L9, P (30) L (25) R (N) C = 1 I = 3
          child(s) 1 of (28)
            [*]ExprId(27) at L9, P (28) L (N) R (N) C = 1 I = 0
              child(s) 1 of (27)
                [*]Id(c)(26) at L9, P (27) L (N) R (N) C = 0 I = 0

```
